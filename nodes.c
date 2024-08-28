/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:43:54 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/08/28 19:48:00 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_lstnew(void)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd) * 1);
	if (node == NULL)
		return (NULL);
	node -> cmd = NULL;
	node -> type = 0;
	node ->redir = NULL;
	node -> prev = NULL;
	node -> next = NULL;
	return (node);
}

t_cmd	*ft_lstlast(t_cmd *lst)
{
	while (lst)
	{
		if (lst -> next == NULL)
			break ;
		lst = lst -> next;
	}
	return (lst);
}

void	ft_lstadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*node;

	if (lst == NULL)
		lst = &new;
	node = ft_lstlast(*lst);
	if (node)
		node -> next = new;
	else
		*lst = new;
}
