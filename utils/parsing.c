#include "../minishell.h"

char	*concat_quote(char *line, char *quote)
{
	char	*concat_line;

	ft_strlcat(line, "\n", ft_strlen(line) + 2);
	concat_line = ft_strjoin(line, readline(quote));
	return (concat_line);
}

int	get_last_status(t_cmd *cmd)
{
	while (cmd && cmd->next)
		cmd = cmd->next;
	return (cmd->status);
}

int	parse_line(char *line, char **env, t_env *str_env)
{
	char	**parsed;
	char	**split;
	int		i;
	t_cmd	*cmd;

	cmd = NULL;
	parsed = split_pipe(line);
	i = 0;
	while (parsed[i])
	{
		split = args_split(parsed[i++]);
		add_next_cmd(&cmd, init_cmd(remove_redirs(split), COMMAND, str_env),
			get_redirs(split));
		free_ptr(split);
	}
	pipex(&cmd, env);
	free_ptr(parsed);
	free_cmd(cmd);
	unlink("temp");
	return (get_last_status(cmd));
}