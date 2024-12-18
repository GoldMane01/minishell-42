/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:18:28 by dramos-n          #+#    #+#             */
/*   Updated: 2024/12/18 11:34:05 by crmunoz-         ###   ########.fr       */
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

void	next_loop(char *line, t_env *str_env, char *dir, int *last_status)
{
	char	*expand_line;

	add_history(line);
	while (close_quote(line))
		line = concat_quote(line, "quote> ");
	expand_line = expand_all(line, str_env, *last_status);
	*last_status = parse_line(expand_line, str_env);
	free(line);
	free(dir);
}

void	loop(t_env *str_env)
{
	char	*line;
	char	*dir;
	int		last_status;

	last_status = 0;
	while (1 + 1 == 2)
	{
		dir = get_dir();
		line = NULL;
		line = readline(dir);
		if (line == NULL)
		{
			free(dir);
			break ;
		}
		if (ft_strcmp(line, "") && ft_strcmp(line, "<")
			&& ft_strcmp(line, ">"))
			next_loop(line, str_env, dir, &last_status);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_env	*str_env;

	if (argc != 1 || !argv)
		exit(1);
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, ctrl_quit_handler);
	str_env = create_env(env);
	loop(str_env);
	rl_clear_history();
	free_env(str_env);
}
