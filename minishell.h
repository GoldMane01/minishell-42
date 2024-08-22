#include <stdio.h>

typedef struct s_env
{
	char	*key;
	char	*value;
	t_env	*next;
}				t_env;