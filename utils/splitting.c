/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliteo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:35:38 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/11/11 16:08:12 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	n_str(char *s, char c)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if ((((s[i + 1] == c) || s[i + 1] == '\0')
				&& s[i] != c) && (s[i] != '\\'))
			n++;
		i++;
	}
	return (n);
}

char	**split_cmd(char *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**ptr;

	i = -1;
	k = 0;
	ptr = malloc(sizeof(char *) * (n_str(s, c) + 1));
	if (!ptr)
		return (NULL);
	while (s[++i])
	{
		if (s[i] != c || (s[i] == c && i > 0 && s[i - 1] == '\\'))
		{
			j = 0;
			while (s[i + j] != c && s[i + j])
				j++;
			ptr[k++] = ft_substr(s, i, j);
			if (!ptr[k - 1])
				return (free_ptr(ptr));
			i += j - 1;
		}
	}
	ptr[k] = NULL;
	return (ptr);
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