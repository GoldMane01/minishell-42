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

#include "../minishell.h"

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

char	return_quote(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	while (ft_isspace(str[i]))
		i++;
	while (quote != str[i])
	{
		if (str[i] == '\\')
			i++;
		else if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		i++;
	}
	return (quote);
}

void	quote_state(int *state, char c)
{
	if (c == '\'')
	{
		if (*state == 1)
			*state = 0;
		else if (*state == 0)
			*state = 1;
	}
	if (c == '\"')
	{
		if (*state == 2)
			*state = 0;
		else if (*state == 0)
			*state = 2;
	}
}