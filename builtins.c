/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris <cris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:06:58 by cris              #+#    #+#             */
/*   Updated: 2024/10/16 20:43:28 by cris             ###   ########.fr       */
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

void	export(t_env *env, char *key, char *value) // nos pueden pasar varios keys y values, así que hay que llamar a esta función por cada uno de ellos
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

void	unset(t_env	**env, char	*key) // si lo borra bien devuelve 0, si no -1
{
	t_env	*current;
	t_env	*temp;

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
