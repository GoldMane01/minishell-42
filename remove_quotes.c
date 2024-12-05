/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 20:49:08 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/12/05 17:33:22 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quote(char *str)
{
	char	*start;
	char	*end;
	char	*dest;

	if (!str || !*str)
		return (str);

	start = str;
	end = str + strlen(str) - 1;
	if (*start == '\'' || *start == '"')
		start++;
	if (end >= start && (*end == '\'' || *end == '"'))
		*end = '\0';
	if (start != str)
	{
		dest = str;
		while (*start)
			*dest++ = *start++;
		*dest = '\0';
	}
	return (str);
}

void	process_quotes(t_cmd *command)
{
	int	i;

	i = 0;
	if (!command || !command->cmd)
		return ;
	while (command->cmd[i])
	{
		command->cmd[i] = remove_quote(command->cmd[i]);
		i++;
	}
}