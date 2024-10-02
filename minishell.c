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
	save_cmd(line);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	*dir;

	char **ennove;
	char **a;
	char **b;
	char **c;

	line = NULL;
	dir = get_dir();
	line = readline(dir);
	

	ennove = split_pipe(line);
	a = args_split(ennove[0]);
	b = args_split(ennove[1]);
	c = args_split(ennove[2]);
	/*t_cmd *cmd;
	cmd = init_cmd(line, COMMAND);*/

	/*t_cmd *node;
	node = cmd;
	int i = 0;
	while (node)
	{
		while (cmd->cmd[i])
		{
			printf("%d- %s\n", i, cmd->cmd[i]);
			i++;
		}
		printf("type- %d\n", cmd->type);

		node = node->next;
	}*/

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

//1-	cmd
//2-	cmd | cmd | cmd
//3-	</> file cmd | cmd
