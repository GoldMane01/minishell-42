#include "../minishell.h"

int	here_doc_eof(char *line, char *eof)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[j])
	{
		while (line[j] != '\n' && line[j] != '\0')
			j++;
		if (line[j] == '\n')
		{
			i = j;
			j++;
		}
	}
	if (!ft_strcmp(line + i + 1, eof))
		return (0);
	return (1);
}

int	open_here_doc(t_redir *fd)
{
	int		temp_fd;
	char	*line;

	temp_fd = open("temp", O_RDWR | O_CREAT | O_TRUNC, 0666);
	line = readline("> ");
	while (here_doc_eof(line, fd->name))
		line = concat_quote(line, "> ");
	write(temp_fd, line, ft_strlen(line));
	close(temp_fd);
	return (temp_fd);
}

t_redir	*get_fd_in(t_cmd *cmd)
{
	t_redir	*fd;
	t_redir	*head;

	fd = NULL;
	head = cmd->redir;
	while (cmd->redir)
	{
		if (cmd->redir->type == INN)
		{
			fd = cmd->redir;
			open_here_doc(fd);
			fd->fd = open("temp", O_RDONLY, 0666);
		}
		if (cmd->redir->type == IN)
		{
			fd = cmd->redir;
			fd->fd = open(fd->name, O_RDONLY, 0666);
		}
		cmd->redir = cmd->redir->next;
	}
	cmd->redir = head;
	return (fd);
}

t_redir	*get_fd_out(t_cmd *cmd)
{
	t_redir	*fd;
	t_redir	*head;

	fd = NULL;
	head = cmd->redir;
	while (cmd->redir)
	{
		if (cmd->redir->type == OUTT || cmd->redir->type == OUT)
		{
			fd = cmd->redir;
			fd->fd = open(fd->name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (fd->fd == -1)
				return (NULL);
		}
		cmd->redir = cmd->redir->next;
	}
	cmd->redir = head;
	return (fd);
}