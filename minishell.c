/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris <cris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:18:28 by dramos-n          #+#    #+#             */
/*   Updated: 2024/10/14 18:59:46 by cris             ###   ########.fr       */
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

char	*concat_quote(char *line)
{
	char	*concat_line;

	ft_strlcat(line, "\n", ft_strlen(line) + 2);
	concat_line = ft_strjoin(line, readline("quote> "));
	return (concat_line);
}

t_redir	*get_fd_in(t_cmd *cmd)
{
	t_redir	*fd;
	t_redir	*head;

	fd = NULL;
	head = cmd->redir;
	while(cmd->redir)
	{
		if (cmd->redir->type == INN || cmd->redir->type == IN)
		{
			fd = cmd->redir;
			open(fd->name, O_RDONLY, 0666);
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
			open(fd->name, O_WRONLY | O_CREAT, 0666);
		}
		cmd->redir = cmd->redir->next;
	}
	cmd->redir = head;
	return (fd);
}

void	execute_cmd(t_cmd **cmd)
{
	t_cmd		*node;
	t_redir		*fdin;
	t_redir		*fdout;

	node = (*cmd);
	fdin = NULL;
	fdout = NULL;
	while (node)
	{
		if (node->redir)
		{
			fdin = get_fd_in(node);
			fdout = get_fd_out(node);
		}
		node = node->next;
	}
}

void	parse_line(char *line)
{
	char	**parsed;
	char	**split;
	int		i;
	t_cmd	*cmd;

	cmd = NULL;
	while (close_quote(line))
		line = concat_quote(line);
	parsed = split_pipe(line);
	i = 0;
	while (parsed[i])
	{
		split = args_split(parsed[i++]);
		add_next_cmd(&cmd, init_cmd(remove_redirs(split), COMMAND), get_redirs(split));
		if (parsed[i])
			add_next_pipe(&cmd);
	}
	execute_cmd(&cmd);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	*dir;
	t_env	*str_env;
	char	*expand_line;

	str_env = create_env(env);
	//line = "ls -alh >>out < in | grep <<inn mini | wc -l > out";
	while (1 + 1 == 2)
	{
		dir = get_dir();
		line = NULL;
		line = readline(dir);
		add_history(line);
		expand_line = expand_arg(line, str_env, 0);
		printf("%s\n", expand_line);
		parse_line(expand_line);
		free(line);
		free(dir);
	}
}
