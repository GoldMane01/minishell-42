/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:34:42 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/11/11 16:05:36 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_each_arg(char *cmd)
{
	int	i;
	int	stateq;

	stateq = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\\' && (cmd[i + 1] == '\'' || cmd[i + 1] == '\"'))
			i += 2;
		if (cmd[i] == '\'' || cmd[i] == '\"')
			quote_state(&stateq, cmd[i]);
		i++;
		if (ft_isspace(cmd[i]) && !stateq)
			break ;
	}
	return (i);
}

int	args_cnt(char *cmd)
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

	i = 0;
	while (*cmd && ft_isspace(*cmd))
		cmd++;
	n_args = args_cnt(cmd);
	args = malloc(sizeof(char *) * (n_args + 1));
	if (!args)
		return (NULL);
	args[n_args] = NULL;
	while (i < n_args)
	{
		len_arg = len_each_arg(cmd);
		args[i] = ft_substr(cmd, 0, len_arg);
		if (!args[i])
			return (free_ptr(args));
		cmd += len_arg;
		while (*cmd && ft_isspace(*cmd))
			cmd++;
		i++;
	}
	return (args);
}
