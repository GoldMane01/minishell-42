/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:53:27 by cris              #+#    #+#             */
/*   Updated: 2024/11/11 15:40:13 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(t_env *env)
{
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void	ft_pwd(void)
{
	char	current_directory[PATH_MAX];

	if (getcwd(current_directory, sizeof(current_directory)) != NULL)
		printf("Current working directory: %s\n", current_directory);
	else
		perror("Error getting the current working directory");
}

int	changedir(char *path)
{
	if (chdir(path) != 0)
	{
		perror("Error changing directory\n");
		return (-1);
	}
	return (0);
}

int	ft_cd(char **cmd)
{
	char	*home_dir;

	if (cmd[1] == NULL)
	{
		home_dir = getenv("HOME");
		if (home_dir != NULL)
			changedir(home_dir);
		else
		{
			printf("Could not determine HOME directory\n");
			return (-1);
		}
	}
	else
		changedir(cmd[1]);
	return (0);
}
