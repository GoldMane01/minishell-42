/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris <cris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:54:10 by cris              #+#    #+#             */
/*   Updated: 2024/11/06 20:18:28 by cris             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		return (1);
	return (0);
}

int	ft_builtins(t_env *env, t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		ft_unset(&env, cmd->cmd[1]);
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
