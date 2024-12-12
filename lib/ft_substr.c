#include "../minishell.h"

char	*ft_substr(char const *s, int start, int len)
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