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