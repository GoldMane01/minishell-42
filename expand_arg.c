/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris <cris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:22:11 by cris              #+#    #+#             */
/*   Updated: 2024/10/10 19:55:48 by cris             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value(char *arg, t_env *env)
{
	char	*key;
	char	*value;
	int		i;

	i = 1;
	while(ft_isalnum(arg[i]))
		i++;
	key = ft_substr(arg, 1, i - 1);
	value = get_env_value(key, env);
	return (value);
}

char	*change_len(char *arg, char *value)
{
	char	*newarg;
	int		i;
	int		j;
	int		stateq;
	char	*chop;

	i = 0;
	j = 0;
	stateq = 0;
	while (arg[i])
	{
		if (arg[i] == '\\')
			i++;
		else if(arg[i] == '\'' || arg[i] == '\"')
			quote_state(&stateq, arg[i]);
		else if(arg[i] == '$' && stateq != 1)
			break;
		i++;
	}
	j = i;
	while (!ft_isspace(arg[j]))
		j++;
	chop = ft_substr(arg, j, (ft_strlen(arg) - j));
	newarg = ft_substr(arg, 0, i);
	newarg = ft_strjoin(newarg, value);
	newarg = ft_strjoin(newarg, chop);
	return (newarg);
}

char *expand_arg(char *arg, t_env *env)
{
	int		i;
	int		stateq;
	char	*value;
	char	*newarg;
	char	*cpyarg;

	i = 0;
	stateq = 0;
	cpyarg = arg;
	while (*arg)
	{
		if (*arg == '\\')
			arg++;
		else if (*arg == '\'' || *arg == '\"')
			quote_state(&stateq, *arg);
		else if (*arg == '$' && stateq != 1)
			value = get_value(arg, env);
		arg++;
	}
	newarg = change_len(cpyarg, value);
	printf("%s\n", newarg);
}