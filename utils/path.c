/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:36:07 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/12/16 19:36:08 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (ft_strcmp(get_env_value("PATH", cmd->env), "") == 0)
		return (path);
	command = malloc(sizeof(char) * (ft_strlen(cmd->cmd[0]) + 2));
	if (!command)
		return (NULL);
	ft_strlcpy(command, "/", 2);
	ft_strlcat(command, cmd->cmd[0],
		ft_strlen(cmd->cmd[0]) + ft_strlen(command) + 1);
	if (is_builtin(cmd->cmd[0]) == 1)
	{
		allpaths = ft_split(get_env_value("PATH", cmd->env), ':');
		allpaths[0] += 5;
		path = check_paths(allpaths, command);
		allpaths[0] -= 5;
		free_ptr(allpaths);
	}
	free(command);
	return (path);
}