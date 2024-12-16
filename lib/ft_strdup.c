/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:59:07 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/12/16 19:19:48 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(char *s1)
{
	int		i;
	char	*dest;
	int		s1len;

	if (!s1)
		return (0);
	i = 0;
	s1len = ft_strlen(s1);
	dest = malloc((sizeof(char) * s1len) + 1);
	if (dest == NULL)
		return (0);
	while (i < s1len)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
