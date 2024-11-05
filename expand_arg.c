/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris <cris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:22:11 by cris              #+#    #+#             */
/*   Updated: 2024/11/05 19:02:49 by cris             ###   ########.fr       */
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
	free_ptr(&key);
	return (value);
}

char	*change_len(char *arg, char *value) //pendiente gestionar bien la memoria de newarg para evitar leaks
{
	char	*newarg;
	int		i;
	int		j;
	int		stateq;
	char	*chop;
	char	*temp;

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
	j = i + 1;
	while (ft_isalnum(arg[j]))
		j++;
	chop = ft_substr(arg, j, (ft_strlen(arg) - j));
	newarg = ft_substr(arg, 0, i);
	temp = ft_strjoin(newarg, value);
	free_ptr(&newarg);
	newarg = ft_strjoin(newarg, chop);
	free_ptr(&temp);
	free_ptr(&chop);
	return (newarg);
}

char *expand_arg(char *arg, t_env *env, int	i) //  la i hay que pasarla a 0, me faltaban variables
{
	int		check;
	int		stateq;
	char	*value;
	char	*newarg;
	char	*cpyarg;

	check = 0;
	stateq = 0;
	cpyarg = arg;
	while (*arg)
	{
		if (*arg == '\\')
			arg++;
		else if (*arg == '\'' || *arg == '\"')
			quote_state(&stateq, *arg);
		else if (*arg == '$' && stateq != 1)
		{
			value = get_value(arg, env);
			check = 1;
		}
		arg++;
	}
	if (check == 1)
		newarg = change_len(cpyarg, value);
	else
		newarg = cpyarg;
	free_ptr(&cpyarg);
	return (newarg);
}