/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseito.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:34:42 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/08/27 19:15:23 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\r' || c == '\f')
		return (1);
	else
		return (0);
}

int	close_quote(char *str) // comprobamos si hay comillas y están cerradas. Si falta el cierre devuelve 1.
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	while (str[i])
	{
		while (!quote && ft_isspace(str[i]))
			i++;
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (str[i] == '\\' && str[i + 1] != '\0')
			i++;
		else if (quote && str[i] == quote)
			quote = 0;
		i++;
	}
	if (quote == 0)
		return (0);
	else
		return (1);
}
