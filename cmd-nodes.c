/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd-nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:51:09 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/09/02 17:24:13 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd *init_cmd(char *file, int i, int type)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(cmd));
	if (!cmd)
		exit(1);
	cmd->cmd = //crear función donde guarde el array
	cmd->type = type;
	cmd->next = NULL;
	cmd->prev = // ???
}

