/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliteo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:35:38 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/09/05 19:55:53 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	n_str(char *s, char c)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if ((((s[i + 1] == c) || s[i + 1] == '\0') && s[i] != c) && (s[i] != '\\'))
			n++;
		i++;
	}
	return (n);
}

char	**spliteo_cmd(char *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**ptr;

	i = -1;
	k = 0;
	ptr = malloc(sizeof(char *) * (n_str(s, c) + 1));
	if (!ptr)
		return (NULL);
	while (s[++i])
	{
		if (s[i] != c || (s[i] == c && i > 0 && s[i - 1] == '\\')) 
		{
			j = 0;
			while (s[i + j] != c && s[i + j])
				j++;
			ptr[k++] = ft_substr(s, i, j);
			if (!ptr[k - 1])
				return (free_ptr(ptr));
			i += j - 1;
		}
	}
	ptr[k] = NULL;
	return (ptr);
}
