/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris <cris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 20:34:21 by cris              #+#    #+#             */
/*   Updated: 2024/11/05 20:44:17 by cris             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_errexit(char *str)
{
	write(2, "exit\n", 5);
	write(2, "bash: exit: ", 12);
	write(2, str, sizeof(str));
	write(2, ": numeric argument required\n", 28);
	exit(255);
}

long	ft_atol(char *str)
{
	int		i = 0;
	long	sign = 1;
	long	n = 0;

	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = (n * 10) + (str[i] - '0');
		if ((sign == 1 && n > LONG_MAX) || (sign == -1 && n > (unsigned long)LONG_MAX + 1))
			return (0);
		i++;
	}
	if (str[i] != '\0')
		return (0);
	return (n * sign);
}

void	ft_exit(t_cmd *command)
{
	long	exit_code;

	if (command->cmd[1] && command->cmd[2])
	{
		write(2, "exit: too many arguments\n", 25);
		return;
	}
	if (command->cmd[1])
	{
		exit_code = ft_atol(command->cmd[1]);
		if (exit_code == 0 && command->cmd[1][0] != '0')
			print_errexit(command->cmd[1]);
		exit((unsigned char)exit_code);
	}
	else
		exit(0);
}