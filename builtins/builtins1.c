/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:06:58 by cris              #+#    #+#             */
/*   Updated: 2024/11/11 16:12:56 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exporting(t_env *env, char *key, char *value) //pueden pasar varios keys y values
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
			return ;
		}
		current = current->next;
	}
	add_env(env, new_env(ft_strdup(key), ft_strdup(value)));
}

void	ft_export(t_env *env, char **cmd)
{
	char	**key_value;
	int		i;

	i = 1;
	while (cmd[i])
	{
		key_value = ft_split(cmd[i], '=');
		ft_exporting(env, key_value[0], key_value[1]);
		free_ptr(key_value);
		i++;
	}
}

int	ft_cont_unset(t_env	**current, t_env **temp, char *key)
{
	while (*current && (*current)->next)
	{
		if (ft_strcmp((*current)->next->key, key) == 0)
		{
			*temp = (*current)->next->next;
			if ((*current)->next->value)
				free((*current)->next->value);
			free((*current)->next->key);
			free ((*current)->next);
			(*current)->next = *temp;
			return (0);
		}
		(*current) = (*current)->next;
	}
	return (-1);
}

int	ft_unset(t_env	**env, char	*key) // si lo borra bien devuelve 0, si no -1
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
		return (0);
	}
	return (ft_cont_unset(&current, &temp, key));
}

void	ft_echo(char **cmd)
{
	int	i;
	int	newline;

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
