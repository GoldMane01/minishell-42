/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:22:11 by cris              #+#    #+#             */
/*   Updated: 2024/12/05 15:31:47 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value(char *arg, t_env *env)
{
	char	*key;
	char	*value;
	int		i;

	i = 1;
	while (ft_isalun(arg[i]))
		i++;
	if (arg[i] != '\0')
		key = ft_substr(arg, 1, i - 1);
	else
		key = ft_substr(arg, 1, i);
	value = get_env_value(key, env);
	free(key);
	return (value);
}

int	count_len(char	*arg)
{
	int	i;
	int	stateq;

	i = 0;
	stateq = 0;
	while (arg[i])
	{
		if (arg[i] == '\\')
			i++;
		else if (arg[i] == '\'' || arg[i] == '\"')
			quote_state(&stateq, arg[i]);
		else if (arg[i] == '$' && stateq != 1)
			break ;
		i++;
	}
	return (i);
}

char	*change_len(char *arg, char *value)
{
	char	*newarg;
	int		i;
	int		j;
	char	*chop;
	char	*temp;

	if (!arg || !value)
		return (NULL);
	i = count_len(arg);
	j = i + 1;
	while (arg[i] && ft_isalun(arg[j]))
		j++;
	if (arg[i - 1] == '\"')
	{
		i--;
		j++;
	}
	chop = ft_substr(arg, j, (ft_strlen(arg) - j));
	newarg = ft_substr(arg, 0, i);
	temp = ft_strjoin(newarg, value);
	free(newarg);
	newarg = ft_strjoin(temp, chop);
	free(temp);
	free(chop);
	return (newarg);
}

char	*expand_arg(char *arg, t_env *env)
{
	int		stateq;
	char	*value;
	char	*cpyarg;

	value = NULL;
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
		if (value)
			break ;
		arg++;
	}
	if (value && arg)
		return (change_len(cpyarg, value));
	return (cpyarg);
}

char	*expand_all(char *arg, t_env *env)
{
	int		i;
	char	*newarg;

	newarg = NULL;
	i = 0;
	while (*arg & arg[i])
	{
		if ((arg[i] == '$') && (arg[i - 1] != '\''))
		{
			newarg = expand_arg(arg, env);
			return (expand_all(newarg, env));
		}
		i++;
	}
	return (arg);
}
