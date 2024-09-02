/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd-nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:51:09 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/09/02 18:22:24 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes(t_cmd *cmd)
{
	t_cmd	*node;
	int		count;

	node = cmd;
	count = 0;
	if (!node)
		return (0);
	while (node)
	{
		if (node->type == PIPE)
			count++;
		node = node->next;
	}
	return (count);
}

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	ptr = 0;
	while (*s != '\0')
	{
		if (*s == (char)c)
		{
			ptr = (char *) s;
			return (ptr);
		}
		s++;
	}
	if ((char)c == '\0')
		ptr = (char *) s;
	return (ptr);
}

char	**create_new_cmd(char **cmd, int count)
{
	char	**new;
	int		i;
	int		j;

	new = malloc(sizeof(char *) * count + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '<' || cmd[i][0] == '>')
		{
			if (ft_strchr(cmd[i], ' '))
				i++;
			i++;
		}
		new[i] = malloc(sizeof(char) * ft_strlen(cmd[i]));
		if (!new[i])
			free_ptr(new);
		j = 0;
		while (cmd[i][j])
		{
			new[i][j] = cmd[i][j];
			j++;
		}
		cmd[i][j] = '\0';
		i++;
	}
	new[i] = NULL;
	return (new);
}

char	**remove_redirs(char **cmd)
{
	int		i;
	char	**new;
	int		count;

	count = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '<' || cmd[i][0] == '>')
		{
			count--;
			if (ft_strchr(cmd[i], ' '))
				count--;
		}
		count++;
	}
	new = create_new_cmd(cmd, count);
	return (new);
}

char	**get_cmd(char *file)
{
	int		i;
	char	**cmd;

	i = 0;
	while (file[i] != '|' && file[i] != '\0')
		i++;
	if (file[i] == '|')
		file[i] = '\0';
	cmd = ft_split(file, ' ');
	cmd = remove_redirs(cmd);
	return (cmd);
}

t_cmd *init_cmd(char *file, int i, int j, int type)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(cmd));
	if (!cmd)
		exit(1);
	if (cmd != PIPE)
		cmd->cmd = get_cmd(file, i, j);
	else
		cmd->cmd = NULL;
	cmd->type = type;
	cmd->next = NULL;
}

