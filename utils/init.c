/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:36:00 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/12/16 19:36:00 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

t_cmd	*init_cmd(char **cmd, int type, t_env *env)
{
	t_cmd	*command;

	command = NULL;
	command = malloc(sizeof(t_cmd));
	if (!command)
		exit(1);
	if (type != PIPE)
	{
		command->cmd = remove_path(cmd);
		command->env = env;
	}
	else
		command->cmd = NULL;
	command->type = type;
	command->next = NULL;
	command->path = NULL;
	command->prev = NULL;
	command->redir = NULL;
	return (command);
}

t_redir	*init_redir(char *str)
{
	t_redir	*redir;

	redir = NULL;
	redir = malloc(sizeof(t_redir));
	if (!redir)
		exit(1);
	redir->name = get_redir_file(str);
	redir->type = get_redir_type(str);
	redir->fd = -1;
	redir->next = NULL;
	return (redir);
}