#include <stdio.h>
#include <stdlib.h>

typedef enum s_type
{
	PIPE,
	COMMAND,
	IN,
	INN,
	OUT,
	OUTT
}

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_redir
{
	char			*name;
	int				type;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**cmd;
	int				type;
	struct s_redir	redir;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;