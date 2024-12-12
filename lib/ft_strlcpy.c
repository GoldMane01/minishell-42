#include "../minishell.h"

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