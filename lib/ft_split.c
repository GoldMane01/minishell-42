/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:58:52 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/12/16 19:19:38 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	count_strs(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if ((s[i + 1] == c || s[i + 1] == '\0') && s[i] != c)
			count++;
		i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**ptr;

	i = -1;
	k = 0;
	ptr = malloc(sizeof(char *) * (count_strs(s, c) + 1));
	if (!ptr)
		return (NULL);
	while (s[++i])
	{
		if (s[i] != c)
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
