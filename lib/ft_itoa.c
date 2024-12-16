/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:47:40 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/12/16 19:17:19 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_intlen(long n)
{
	int	len;

	len = 0;
	if (n == 0)
	{
		len++;
		return (len);
	}
	if (n < 0)
	{
		n = n * -1;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		len;
	long	num;

	num = n;
	len = ft_intlen (num);
	s = (char *) malloc (sizeof (char) * (len + 1));
	if (!s)
		return (0);
	s[len--] = '\0';
	if (n == 0)
		s[0] = '0';
	if (num < 0)
	{
		s[0] = '-';
		num = num * -1;
	}
	while (num > 0)
	{
		s[len] = (num % 10) + '0';
		num = num / 10;
		len--;
	}
	return (s);
}
