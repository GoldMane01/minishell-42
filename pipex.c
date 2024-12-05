/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:06:16 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/12/05 17:28:52 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_strequal(char *ptr, const char *needle, size_t len)
{
	int	count;

	count = 0;
	while (*needle != '\0' && len > 0)
	{
		if (*ptr != *needle)
			return (0);
		len--;
		ptr++;
		needle++;
		count++;
	}
	if (len == 0 && *needle != '\0')
		return (0);
	return (1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*ptr;

	ptr = (char *)haystack;
	if (*needle == '\0')
		return (ptr);
	while (len > 0 && *haystack != '\0')
	{
		if (*haystack == *needle)
		{
			ptr = (char *)haystack;
			if (check_strequal(ptr, needle, len))
				return (ptr);
		}
		haystack++;
		len--;
	}
	return (0);
}

int	check_access(char *path, char *command)
{
	char	*ptr;
	char	**cmdsplit;

	cmdsplit = ft_split(command, ' ');
	ptr = malloc(sizeof(char) * (ft_strlen(path) + ft_strlen(cmdsplit[0]) + 1));
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, path, ft_strlen(path) + 1);
	ft_strlcat(ptr, cmdsplit[0], ft_strlen(path) + ft_strlen(cmdsplit[0]) + 1);
	free_ptr(cmdsplit);
	if (access(ptr, F_OK) != 0)
	{
		free(ptr);
		return (0);
	}
	free(ptr);
	return (1);
}

char	**find_paths(char *envp[])
{
	char	**paths;
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], "PATH", 5))
			break ;
		i++;
	}
	paths = ft_split(envp[i], ':');
	return (paths);
}

char	*get_path(char *path, char *command)
{
	char	*ptr;
	char	**cmdsplit;

	cmdsplit = ft_split(command, ' ');
	ptr = malloc(sizeof(char) * (ft_strlen(path) + ft_strlen(cmdsplit[0]) + 1));
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, path, ft_strlen(path) + 1);
	ft_strlcat(ptr, cmdsplit[0], ft_strlen(path) + ft_strlen(cmdsplit[0]) + 1);
	free_ptr(cmdsplit);
	return (ptr);
}

// A PARTIR DE AQUÍ HAY QUE PASAR TODAS LAS FUNCIONES A OTRO ARCHIVO
char	*check_paths(char **allpaths, char *command)
{
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	while (allpaths[i])
	{
		if (check_access(allpaths[i], command))
		{
			path = get_path(allpaths[i], command);
			break ;
		}
		i++;
	}
	return (path);
}

char	*cmdpath(t_cmd *cmd, char **env)
{
	char	**allpaths;
	char	*path;
	char	*command;

	path = NULL;
	command = malloc(sizeof(char) * (ft_strlen(cmd->cmd[0]) + 2));
	if (!command)
		return (NULL);
	ft_strlcpy(command, "/", 2);
	ft_strlcat(command, cmd->cmd[0],
		ft_strlen(cmd->cmd[0]) + ft_strlen(command) + 1);
	if (is_builtin(cmd->cmd[0]) == 1)
	{
		allpaths = find_paths(env);
		allpaths[0] += 5;
		path = check_paths(allpaths, command);
		allpaths[0] -= 5;
		free_ptr(allpaths);
	}
	free(command);
	return (path);
}

//esta función tiene muchos argumentos
void	execute(t_cmd *cmd, t_redir *fdin, t_redir *fdout, int fd[], int fd_in) 
{
	int	pid;

	if (ft_builtins_nopipe(cmd->env, cmd) == -1)
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
				if (execve(cmd->path, cmd->cmd, NULL) == -1) //hay que guardar el número que devuelve execve en alguna estructura
					exit(1);
			exit(0);
		}
		close(fd[1]);
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		waitpid(pid, NULL, 0);
	}
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
		execute(node, fdin, fdout, fd, fd_in);
		fd_in = fd[0];
		node = node->next;
		while (node && node->type == PIPE)
			node = node->next;
	}
	if (fd_in != STDIN_FILENO)
		close(fd_in);
}
