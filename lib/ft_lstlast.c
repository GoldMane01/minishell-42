/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:58:46 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/12/16 18:58:47 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*ft_lstlast(t_cmd *lst)
{
	t_cmd	*node;

	node = lst;
	while (node)
	{
		if (node->next)
			node = node->next;
		else
			break ;
	}
	return (node);
}