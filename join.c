/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:22:41 by dramos-n          #+#    #+#             */
/*   Updated: 2024/09/02 20:38:33 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dlen;
	size_t	slen;
	int		i;

	i = 0;
	dlen = 0;
	slen = 0;
	while (dst[dlen] != '\0')
		dlen++;
	while (src[slen] != '\0')
		slen++;
	if (dstsize <= dlen)
		slen += dstsize;
	else
		slen += dlen;
	while (src[i] != '\0' && (dlen + 1) < dstsize)
	{
		dst[dlen] = src[i];
		dlen++;
		i++;
	}
	dst[dlen] = '\0';
	return (slen);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	while (src[i] != '\0')
		i++;
	if (dstsize <= 0)
		return (i);
	while (src[count] != '\0' && count < (dstsize - 1))
	{
		dst[count] = src[count];
		count++;
	}
	if (dstsize)
		dst[count] = '\0';
	return (i);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;

	ptr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (ptr)
	{
		ft_strlcpy(ptr, s1, ft_strlen(s1) + 1);
		ft_strlcat(ptr, s2, ft_strlen(s2) + ft_strlen(s1) + 1);
	}
	return (ptr);
}
