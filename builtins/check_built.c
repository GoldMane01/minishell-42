/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris <cris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:54:10 by cris              #+#    #+#             */
/*   Updated: 2024/11/06 19:54:49 by cris             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_builtins(t_env *env, t_cmd *cmd) //si devuelve 0 es que el cmd era uno de la lista y lo ha ejecutado
{
	if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		ft_unset(env, cmd->cmd[1]);
	else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		ft_cd(cmd->cmd);
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		ft_export(env, cmd->cmd);
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
		ft_exit(cmd->cmd);
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		print_env(env);
	else if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		ft_echo(cmd->cmd);
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		ft_pwd();
	else
		return (-1);
	return (0);
}
