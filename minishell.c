/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:18:28 by dramos-n          #+#    #+#             */
/*   Updated: 2024/09/05 20:06:23 by crmunoz-         ###   ########.fr       */
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

char	*concat_quote(char *line) /*NO FUNCIONA T_T */ /*COMO QUE NO, CLARO QUE SI :^)*/
{
	char	*concat_line;

	ft_strlcat(line, "\n", ft_strlen(line) + 2);
	concat_line = ft_strjoin(line, readline("quote> "));
	return (concat_line);
}

void	parse_line(char *line)
{
	while (close_quote(line))
		line = concat_quote(line);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	*dir;
	t_cmd	*cmd;

	char **ennove;
	char **red1;
	char **red2;
	char **red3;
	char **a;
	char **b;
	char **c;
	cmd = NULL;

	line = NULL;
	dir = get_dir();
	//line = readline(dir);
	line = "ls -alh >>out < in | grep <<inn mini | wc -l > out";
	
	ennove = split_pipe(line);
	a = args_split(ennove[0]);
	add_next_cmd(&cmd, init_cmd(remove_redirs(a), COMMAND));
	cmd->redir = get_redirs(a);
	b = args_split(ennove[1]);
	add_next_cmd(&cmd, init_cmd(remove_redirs(b), COMMAND));
	cmd->next->redir = get_redirs(b);
	c = args_split(ennove[2]);
	add_next_cmd(&cmd, init_cmd(remove_redirs(c), COMMAND));
	cmd->next->next->redir = get_redirs(c);

	/*while (1 + 1 == 2)
	{
		dir = get_dir();
		line = NULL;
		line = readline(dir);
		add_history(line);
		parse_line(line);
		free(line);
		free(dir);
	}*/
}
