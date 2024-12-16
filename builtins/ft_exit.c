/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 20:34:21 by cris              #+#    #+#             */
/*   Updated: 2024/12/16 20:34:16 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	int		i;
	long	sign;
	long	n;

	i = 0;
	sign = 1;
	n = 0;
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
		if ((sign == 1 && n > LONG_MAX)
			|| (sign == -1 && (unsigned long)n > (unsigned long)LONG_MAX + 1))
			return (0);
		i++;
	}
	if (str[i] != '\0')
		return (0);
	return (n * sign);
}

void	ft_exit(char **cmd)
{
	long	exit_code;

	if (cmd[1] && cmd[2])
	{
		write(2, "exit: too many arguments\n", 25);
		return ;
	}
	if (cmd[1])
	{
		if (ft_isdigit(cmd[1]) != 1)
		{
			write(2, "exit: numeric argument required\n", 32);
			return ;
		}
		exit_code = ft_atol(cmd[1]);
		if (exit_code == 0 && cmd[1][0] != '0')
			print_errexit(cmd[1]);
		rl_clear_history();
		exit((unsigned char)exit_code);
	}
	else
	{
		rl_clear_history();
		exit(0);
	}
}
