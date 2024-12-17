/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:36:04 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/12/16 19:44:49 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	parse_line(char *line, t_env *str_env)
{
	char	**parsed;
	char	**split;
	int		i;
	t_cmd	*cmd;
	int		status;

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
	pipex(&cmd);
	status = get_last_status(cmd);
	free_ptr(parsed);
	free_cmd(cmd);
	unlink("temp");
	return (status);
}
