/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:47:16 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/12/17 16:53:36 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**allocate_new_cmd(int count)
{
	char	**new;

	new = malloc(sizeof(char *) * (count + 1));
	if (!new)
		return (NULL);
	return (new);
}

void	copy_cmd(char **new, char **cmd, int *i, int *k)
{
	int	j;

	j = 0;
	new[*k] = malloc(sizeof(char) * (ft_strlen(cmd[*i]) + 1));
	if (!new[*k])
	{
		free_ptr(new);
		return ;
	}
	while (cmd[*i][j])
	{
		new[*k][j] = cmd[*i][j];
		j++;
	}
	new[*k][j] = '\0';
	(*i)++;
	(*k)++;
}

char	**create_new_cmd(char **cmd, int count)
{
	char	**new;
	int		i;
	int		k;

	new = allocate_new_cmd(count);
	if (!new)
		return (NULL);
	i = 0;
	k = 0;
	while (cmd[i])
	{
		while (cmd[i] && (cmd[i][0] == '<' || cmd[i][0] == '>'))
		{
			i++;
			if (cmd[i] && ft_strlen(cmd[i - 1]) <= 2)
				i++;
		}
		if (!cmd[i])
			break ;
		copy_cmd(new, cmd, &i, &k);
	}
	new[k] = NULL;
	return (new);
}
