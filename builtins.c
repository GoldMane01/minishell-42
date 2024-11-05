/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris <cris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:06:58 by cris              #+#    #+#             */
/*   Updated: 2024/11/05 18:52:25 by cris             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *env)
{
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void	ft_export(t_env *env, char *key, char *value) // nos pueden pasar varios keys y values, así que hay que llamar a esta función por cada uno de ellos
{
	t_env	*current;

	current = env;

	while (current)
	{
		if (ft_strcmp(current->key, key) == 0 && value)
		{
			if (current->value)
				free(current->value);
			current->value = ft_strdup(value);
			return;
		}
		current = current->next;
	}
	add_env(env, new_env(ft_strdup(key), ft_strdup(value)));
}

void	ft_unset(t_env	**env, char	*key) // si lo borra bien devuelve 0, si no -1
{
	t_env	*current;
	t_env	*temp;

	if (!env || !*env || !key)
		return (-1);
	current = (*env);
	if (ft_strcmp(current->key, key) == 0)
	{
		temp = current->next;
		if (current->value)
			free(current->value);
		free(current->key);
		free (current);
		(*env) = temp;
		return(0);
	}
	while (current && current->next)
	{
		if (ft_strcmp(current->next->key, key) == 0)
		{
			temp = current->next->next;
			if (current->next->value)
				free(current->next->value);
			free(current->next->key);
			free (current->next);
			current->next = temp;
			return (0);
		}
		current = current->next;
	}
	return (-1);
}

void	ft_echo(char **cmd)
{
	int i;
	int newline;
	
	i = 1;
	newline = 0;
	if (ft_strcmp(cmd[1], "-n") == 0)
	{
		newline = 1;
		i++;
	}
	while (cmd[i] && cmd[i + 1])
	{
		printf("%s ", cmd[i]);
		i++;
	}
		printf("%s", cmd[i]);
	if (!newline)
		printf("\n");
}

void	ft_pwd(void)
{
	char current_directory[PATH_MAX];

	if (getcwd(current_directory, sizeof(current_directory)) != NULL)
		printf("Directorio actual: %s\n", current_directory);
	else
		perror("Error al obtener el directorio actual");
}

int changedir(char *path)
{
	if (chdir(path) != 0)
	{
		perror("Error al cambiar de directorio");
		return (-1);
	}
	return (0);
}

int ft_cd(char **cmd) //estoy dando por hecho que cmd[0]= "cd", y que por siguiente, lo que haya en cmd[1] será la ruta
{
	char *home_dir;

	if (cmd[1] == NULL) 
	{
		home_dir = getenv("HOME");
		if (home_dir != NULL) 
		{
			changedir(home_dir);
		} else 
		{
			printf("No se proporcionó directorio y no se pudo obtener HOME.\n");
			return (-1);
		}
	}
	else
		changedir(cmd[1]);
	return (0);
}

