/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:34:35 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/12/16 19:34:45 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_redir(t_redir *redir)
{
	t_redir	*aux;

	aux = redir;
	while (aux)
	{
		aux = redir->next;
		free(redir->name);
		free(redir);
		redir = aux;
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*aux;

	aux = cmd;
	while (aux)
	{
		aux = cmd->next;
		if (cmd->type == COMMAND)
		{
			free_ptr(cmd->cmd);
			if (cmd->path != NULL)
				free(cmd->path);
			free_redir(cmd->redir);
		}
		free(cmd);
		cmd = aux;
	}
}

char	**free_ptr(char	**ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	if (ptr)
		free(ptr);
	return (NULL);
}
