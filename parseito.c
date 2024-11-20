/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseito.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:34:42 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/11/20 16:50:21 by crmunoz-         ###   ########.fr       */
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

int	close_quote(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	while (str && str[i])
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

int	get_n_pipe(char *str)
{
	int		pipes;
	char	quote;
	int		i;

	i = 0;
	quote = '\0';
	pipes = 1;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (str[i] == '|' && !quote)
			pipes++;
		i++;
		if (quote == str[i] && str[i - 1] != '\\')
			quote = '\0';
	}
	return (pipes);
}

char	**split_pipe(char *str)
{
	char	**commands;
	int		i;
	char	quote;
	int		j;
	int		k;

	i = 0;
	quote = '\0';
	j = 0;
	k = 0;
	commands = malloc(sizeof(char *) * (get_n_pipe(str) + 1));
	while (str[i])
	{
		j = i;
		while (str[i] && (str[i] != '|' || quote))
		{
			if (str[i] == '\\' && str[i + 1])
				i++;
			else if (!quote && (str[i] == '\'' || str[i] == '\"'))
				quote = str[i];
			else if (quote && str[i] == quote)
				quote = '\0';
			i++;
		}
		commands[k++] = ft_substr(str, j, i - j);
		if (str[i] == '|')
			i++;
	}
	commands[k] = NULL;
	return (commands);
}
