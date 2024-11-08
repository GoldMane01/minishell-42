/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris <cris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:18:28 by dramos-n          #+#    #+#             */
/*   Updated: 2024/10/15 19:31:58 by cris             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_dir(void)
{
	char	buffer[1024];
	char	*dir;
	int		i;

	getcwd(buffer, 1024);
	i = 0;
	while (buffer[i])
		i++;
	dir = malloc(sizeof(char) * (i + 3));
	if (!dir)
		exit(1);
	i = -1;
	while (buffer[++i])
		dir[i] = buffer[i];
	dir[i] = '>';
	dir[i + 1] = ' ';
	dir[i + 2] = '\0';
	return (dir);
}

char	*concat_quote(char *line, char *quote)
{
	char	*concat_line;

	ft_strlcat(line, "\n", ft_strlen(line) + 2);
	concat_line = ft_strjoin(line, readline(quote));
	return (concat_line);
}

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
	if (!strcmp(line + i + 1, eof))
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
	while(cmd->redir)
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
	while(cmd->redir)
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

void	parse_line(char *line, char **env)
{
	char	**parsed;
	char	**split;
	int		i;
	t_cmd	*cmd;

	cmd = NULL;
	while (close_quote(line))
		line = concat_quote(line, "quote> ");
	parsed = split_pipe(line);
	i = 0;
	while (parsed[i])
	{
		split = args_split(parsed[i++]);
		add_next_cmd(&cmd, init_cmd(remove_redirs(split), COMMAND), get_redirs(split));
		if (parsed[i])
			add_next_pipe(&cmd);
	}
	pipex(&cmd, env);
	unlink("temp");
}

void	ctrl_c_handler(int sig)
{
	signal(sig, SIG_IGN);
	printf("\n");
	rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
	signal(SIGINT, ctrl_c_handler);
}

void	ctrl_quit_handler(int sig)
{
	signal(sig, SIG_IGN);
	printf("\n");
	printf("Quit (core dumped)\n");
	rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay(); 
	signal(SIGQUIT, ctrl_quit_handler);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	*dir;
	//t_env	*str_env;
	char	*expand_line;

	if (argc != 1 || !argv)
		exit(1);
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, ctrl_quit_handler);
	//str_env = create_env(env);
	//line = "ls -alh >>out < in | grep <<inn mini | wc -l > out";
	while (1 + 1 == 2)
	{
		dir = get_dir();
		line = NULL;
		line = readline(dir);
		if (line == NULL)
			exit(0);
		add_history(line);
		expand_line = line;
		//expand_line = expand_arg(line, str_env, 0);
		//printf("%s\n", expand_line);
		parse_line(expand_line, env);
		free(line);
		free(dir);
	}
}
