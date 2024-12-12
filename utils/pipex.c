/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:06:16 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/12/11 17:07:16 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_cmd *cmd, t_redir *fdin, t_redir *fdout, int fd[], int fd_in) 
{
	int	pid;
	int status;

	status = 0;
	if (cmd->next == NULL && cmd->prev == NULL &&
		is_builtin_nopipe(cmd->cmd[0]) == 0)
		ft_builtins_nopipe(cmd->env, cmd);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (fdin)
				dup2(fdin->fd, STDIN_FILENO);
			else if (fd_in != STDIN_FILENO)
				dup2(fd_in, STDIN_FILENO);
			if (fdout)
				dup2(fdout->fd, STDOUT_FILENO);
			else if (cmd->next)
				dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			if (ft_builtins_pipe(cmd->env, cmd) == -1)
				if (execve(cmd->path, cmd->cmd, NULL) == -1)
					exit(1);
			exit(0);
		}
		close(fd[1]);
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		waitpid(pid, &status, 0);
	}
	return (status);
}

void	pipex(t_cmd **cmd, char **env)
{
	int			fd[2];
	int			fd_in;
	t_cmd		*node;
	t_redir		*fdin;
	t_redir		*fdout;

	node = *cmd;
	fd_in = STDIN_FILENO;
	while (node)
	{
		fdin = get_fd_in(node);
		fdout = get_fd_out(node);
		process_quotes(node);
		if (pipe(fd) == -1)
			exit(1);
		node->path = cmdpath(node, env);
		node->status = execute(node, fdin, fdout, fd, fd_in);
		fd_in = fd[0];
		node = node->next;
	}
	if (fd_in != STDIN_FILENO)
		close(fd_in);
}
