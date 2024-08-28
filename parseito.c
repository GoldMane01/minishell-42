/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseito.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:34:42 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/08/28 17:45:35 by crmunoz-         ###   ########.fr       */
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

t_cmd	save_cmd(char *str)
{
	int		i;
	int		j;
	char	quote;
	int		esc;

	i = 0;
	quote = '\0';
	esc = 0;
	while (ft_isspace(str[i]) && !quote && !esc)
		i++;
	while (str[i])
	{
		while (str[i] != ' ' || str[i] != '\t')
		{
			if (!esc && str[i] == '\\')
				esc = 1;
			else if (!esc && !quote && (str[i] == '\'' || str[i] == '\"'))
			{
				quote = str[i];
				j = i + 1;
			}
			else if (!esc && quote == str[i])
				quote = '\0';
			else if (!esc && !quote && ((str[i] == '<' && str[i + 1] == '<')
					|| (str[i] == '>' && str[i + 1] == '>')
					|| (str[i] == '<' || str[i] == '>')))
				j = i;
			else if (esc)
				esc = 0;
			i++;
		}

		
	}
}
