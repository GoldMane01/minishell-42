/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris <cris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:22:11 by cris              #+#    #+#             */
/*   Updated: 2024/10/08 20:46:29 by cris             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char    *get_value(char *arg, t_env *env)
{
    char    *key;
    char    *value;
    int     i;

    i = 1;
    while(!ft_isspace(arg[i]))
        i++;
    key = ft_substr(arg, 1, i - 1);
    value = get_env_value(key, env);
    printf("%s", value);
    return (value);
}

char *expand_arg(char *arg, t_env *env)
{
    int i;
    int stateq;
    char    *value;

    i = 0;
    stateq = 0;
    while (arg)
    {
        if (*arg == '\\')
            arg++;
        else if (*arg == '\'' || *arg == '\"')
            quote_state(&stateq, *arg);
        else if (*arg == '$' && stateq != 1)
            value = get_value(arg, env);
        arg++;
    }

}