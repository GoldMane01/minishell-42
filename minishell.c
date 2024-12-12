/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:18:28 by dramos-n          #+#    #+#             */
/*   Updated: 2024/12/11 17:43:40 by crmunoz-         ###   ########.fr       */
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

int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	*dir;
	t_env	*str_env;
	char	*expand_line;
	int		last_status;

	last_status = 0;
	if (argc != 1 || !argv)
		exit(1);
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, ctrl_quit_handler);
	str_env = create_env(env);
	while (1 + 1 == 2)
	{
		dir = get_dir();
		line = NULL;
		line = readline(dir);
		if (line == NULL)
			exit(0);
		add_history(line);
		while (close_quote(line))
			line = concat_quote(line, "quote> ");
		expand_line = expand_all(line, str_env, last_status);
		last_status = parse_line(expand_line, env, str_env);
		free(line);
		free(dir);
	}
	rl_clear_history();
	free(str_env);
}
