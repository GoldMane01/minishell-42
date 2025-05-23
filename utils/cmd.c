/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:51:09 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/12/17 16:54:53 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**second_cmd(char **total, char **cmd2, char **quote, int *j)
{
	int	k;
	int	i;

	k = 0;
	if (quote[2])
	{
		while (cmd2[k])
		{
			total[*j] = malloc((sizeof(char) * (ft_strlen(cmd2[k] + 1))));
			if (!total[*j])
				free_ptr(total);
			i = 0;
			while (cmd2[k][i])
			{
				total[*j][i] = cmd2[k][i];
				i++;
			}
			total[*j][i] = '\0';
			k++;
			j++;
		}
	}
	return (total);
}

char	**first_cmd(char **total, char **cmd, int *j)
{
	int	i;

	while (cmd[*j])
	{
		total[*j] = malloc((sizeof(char) * (ft_strlen(cmd[*j] + 1))));
		if (!total[*j])
			free_ptr(total);
		i = 0;
		while (cmd[*j][i])
		{
			total[*j][i] = cmd[*j][i];
			i++;
		}
		total[*j][i] = '\0';
		*j = *j + 1;
	}
	return (total);
}

char	**totalcmd(char **total, char **cmd, char **cmd2, char **quote)
{
	int	j;
	int	i;

	j = 0;
	total = first_cmd(total, cmd, &j);
	if (quote[1])
	{
		total[j] = malloc((sizeof(char) * (ft_strlen(quote[1] + 1))));
		if (!total[j])
			free_ptr(total);
	}
	i = 0;
	while (quote[1][i])
	{
		total[j][i] = quote[1][i];
		i++;
	}
	total[j][i] = '\0';
	j++;
	total = second_cmd(total, cmd2, quote, &j);
	total[++j] = NULL;
	return (total);
}

t_cmd	*add_next_cmd(t_cmd **head, t_cmd *new, t_redir *redirs)
{
	t_cmd	*node;

	node = *head;
	new->redir = redirs;
	if (!(*head))
		*head = new;
	else
	{
		node = ft_lstlast(*head);
		node->next = new;
		node->next->prev = node;
	}
	return (*head);
}
