/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:06:16 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/12/16 19:45:21 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_process(t_cmd *cmd, t_fd *fd_pipe, int fd[], int fd_in)
{
	if (fd_pipe->fdin)
		dup2(fd_pipe->fdin->fd, STDIN_FILENO);
	else if (fd_in != STDIN_FILENO)
		dup2(fd_in, STDIN_FILENO);
	if (fd_pipe->fdout)
		dup2(fd_pipe->fdout->fd, STDOUT_FILENO);
	else if (cmd->next)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (ft_builtins_pipe(cmd->env, cmd) == -1)
		if (execve(cmd->path, cmd->cmd, NULL) == -1)
			exit(1);
	exit(0);
}

int	execute(t_cmd *cmd, t_fd *fd_pipe, int fd[], int fd_in)
{
	int	pid;
	int	status;

	status = 0;
	if (cmd->next == NULL && cmd->prev == NULL
		&& is_builtin_nopipe(cmd->cmd[0]) == 0)
		ft_builtins_nopipe(cmd->env, cmd);
	else
	{
		pid = fork();
		if (pid == 0)
			child_process(cmd, fd_pipe, fd, fd_in);
		close(fd[1]);
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		waitpid(pid, &status, 0);
	}
	return (status);
}

void	pipex(t_cmd **cmd)
{
	int			fd[2];
	int			fd_in;
	t_cmd		*node;
	t_fd		*fd_pipe;

	node = *cmd;
	fd_in = STDIN_FILENO;
	fd_pipe = malloc(sizeof(t_fd) * 1);
	while (node)
	{
		fd_pipe->fdin = get_fd_in(node);
		fd_pipe->fdout = get_fd_out(node);
		process_quotes(node);
		if (pipe(fd) == -1)
			exit(1);
		node->path = cmdpath(node);
		node->status = execute(node, fd_pipe, fd, fd_in);
		fd_in = fd[0];
		node = node->next;
	}
	free(fd_pipe);
	if (fd_in != STDIN_FILENO)
		close(fd_in);
}
