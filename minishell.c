/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris <cris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:18:28 by dramos-n          #+#    #+#             */
/*   Updated: 2024/10/08 20:40:46 by cris             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_dir(void)
{
	char	buffer[1024];
	char	*dir;
	int		i;

	getcwd(buffer, 1024);
	i = 0;
	while (buffer[i])
		i++;
	dir = malloc(sizeof(char) * (i + 3));
	if (!dir)
		exit(1);
	i = -1;
	while (buffer[++i])
		dir[i] = buffer[i];
	dir[i] = '>';
	dir[i + 1] = ' ';
	dir[i + 2] = '\0';
	return (dir);
}

char	*concat_quote(char *line)
{
	char	*concat_line;

	ft_strlcat(line, "\n", ft_strlen(line) + 2);
	concat_line = ft_strjoin(line, readline("quote> "));
	return (concat_line);
}

void	parse_line(char *line)
{
	char	**parsed;
	char	**split;
	int		i;
	t_cmd	*cmd;

	cmd = NULL;
	while (close_quote(line))
		line = concat_quote(line);
	parsed = split_pipe(line);
	i = 0;
	while (parsed[i])
	{
		split = args_split(parsed[i++]);
		add_next_cmd(&cmd, init_cmd(remove_redirs(split), COMMAND));
		if (parsed[i])
			add_next_pipe(&cmd);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	*dir;

	//line = "ls -alh >>out < in | grep <<inn mini | wc -l > out";
	while (1 + 1 == 2)
	{
		dir = get_dir();
		line = NULL;
		line = readline(dir);
		add_history(line);
		parse_line(line);
		free(line);
		free(dir);
	}
}
