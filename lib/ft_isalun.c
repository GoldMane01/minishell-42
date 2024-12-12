#include "../minishell.h"

int	ft_isalun(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
			|| c == '_')
		return (1);
	else
		return (0);
}