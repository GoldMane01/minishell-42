/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:59:14 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/12/16 19:19:53 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
