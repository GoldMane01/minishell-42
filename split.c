/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 14:21:08 by dramos-n          #+#    #+#             */
/*   Updated: 2024/09/02 20:41:41 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;

	if (!s)
		return (0);
	if (ft_strlen(s) < start)
	{
		ptr = malloc(sizeof(char) * (1));
		if (ptr)
		{
			*ptr = '\0';
			return (ptr);
		}
	}
	else
	{
		if (ft_strlen(s + start) < len)
			len = ft_strlen(s + start);
		if (ft_strlen(s + start) > len)
			ptr = (char *)malloc(sizeof(char) * (len + 1));
		else
			ptr = (char *)malloc(sizeof(char) * (ft_strlen(s + start) + 1));
		if (ptr)
			ft_strlcpy(ptr, s + start, len + 1);
	}
	return (ptr);
}

char	*ft_strdup(char *s1)
{
	int		i;
	char	*dest;
	int		s1len;

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

char	**free_ptr(char	**ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
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
