/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:34:42 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/10/02 16:48:13 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void quote_state(int *state, char c)
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

int	next_arg_len(char *cmd)
{
	int	i;
	int	stateq;

	stateq = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
			quote_state(&stateq, cmd[i]);
		i++;
		if (ft_isspace(cmd[i]) && !stateq)
			break ;
	}
	return (i);
}

int	arg_cnt(char *cmd)
{
	int	i;
	int	n;
	int	stateq;

	stateq = 0;
	n = 0;
	i = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i] == '\\')
			i++;
		if (cmd[i] == '\'' || cmd[i] == '\"')
			quote_state(&stateq, cmd[i]);
		i++;
		if (ft_isspace(cmd[i]) && !stateq)
		{
			while (cmd[i] && ft_isspace(cmd[i]))
				i++;
			if (cmd[i])
				n++;
		}
	}
	if (stateq == 0)
		n++;
	return (n);
}

char	**args_split(char *cmd)
{
	char	**args;
	int		n_args;
	int		len_arg;
	int		i;
	int		start;

	i = 0;
	while (*cmd && ft_isspace(*cmd))
		cmd++;
	n_args = arg_cnt(cmd);
	args = malloc(sizeof(char *) * (n_args + 1));
	args[n_args] = NULL;
	while (i < n_args)
	{
		len_arg = next_arg_len(cmd);
		args[i] = ft_substr(cmd, 0, len_arg);
		cmd += len_arg;
		while (*cmd && ft_isspace(*cmd))
			cmd++;
		i++;
	}
	return (args);
}
