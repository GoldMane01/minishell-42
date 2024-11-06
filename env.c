/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris <cris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:12:09 by dramos-n          #+#    #+#             */
/*   Updated: 2024/10/15 18:13:11 by cris             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_env_key(char *env)
{
	char	*key;
	int		i;
	
	i = 0;
	while (env[i] != '=')
		i++;
	key = malloc(sizeof(char) * (i + 1));
	if (key == NULL)
		exit(1);
	i = -1;
	while (env[++i] != '=')
		key[i] = env[i];
	key[i] = '\0';
	return (key);
}

char	*set_env_value(char *env)
{
	char	*value;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	while (env[i] != '=')
		i++;
	while (env[j + i + 1])
		j++;
	value = malloc(sizeof(char) * (j + 1));
	if (value == NULL)
		exit(1);
	j = 0;
	while (env[i + 1])
	{
		value[j] = env[i + 1];
		j++;
		i++;
	}
	value[j] = '\0';
	return (value);
}

t_env	*new_env(char *key_data, char *val_data)
{
	t_env	*env_node;

	env_node = malloc(sizeof(t_env));
	if (env_node == NULL)
		exit(1);
	env_node->key = key_data;
	env_node->value = val_data;
	env_node->next = NULL;
	return (env_node);
}

void	add_env(t_env *head, t_env *new)
{
	t_env	*aux;

	aux = head;
	while (aux->next)
		aux = aux->next;
	aux->next = new;
}

t_env	*create_env(char **env)
{
	t_env	*struct_env;
	int		i;

	i = 1;
	struct_env = new_env(set_env_key(env[0]), set_env_value(env[0]));
	while (env[i])
	{
		add_env(struct_env, new_env(set_env_key(env[i]), set_env_value(env[i])));
		i++;
	}
	return (struct_env);
}

char	*get_env_value(char *key, t_env *head)
{
	t_env	*node;

	node = head;
	while (node)
	{
		if (ft_strcmp(node->key, key) == 0)
			return (node->value);
		node = node->next;
	}
	return ("");
}
