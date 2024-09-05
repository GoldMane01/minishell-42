/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd-nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:51:09 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/09/05 15:45:18 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	return_quote(char *str)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	quote = '\0';
	while (ft_isspace(str[i]))
		i++;
	while (quote != str[i])
	{
		if (str[i] == '\\')
			i++;
		else if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		i++;
	}
	return (quote);
}

char	**quote_split(char *str)
{
	char	**quote;
	char	**cmd;
	char	**cmd2;
	char	**totalcmd;
	int 	j;
	int		k;
	
	k = -1;
	j = -1;
	quote = ft_split(str, return_quote(str));
	cmd = ft_split(quote[0], ' ');
	if (!quote[1])
		return (cmd);
	else
	{
		while (cmd[++j])
		if (quote[2])
		{
			cmd2 = ft_split(quote[2], ' ');
			while (cmd2[++k])
		}
		totalcmd = malloc(sizeof(char *) * (j + k + 1));
		k = 0;
		j = -1;
		while (cmd[++j])
			totalcmd[j] = cmd[j];
		totalcmd[j++] = quote[1];
		if (quote[2])
		{	while (cmd2[k])
			{
				totalcmd[j] = cmd2[k];
				k++;
				j++;
			}}
		totalcmd[j] = NULL;
		return (totalcmd);
	}
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

t_cmd	*init_cmd(char *str) /*-> ESTÁ A MEDIO HACER, SÓLO LO PONGO POR TENERLO EN CUENTA */
{
	t_cmd	*command;

	command = malloc(sizeof(command));
	if (!command)
		exit(1);
	command->cmd = remove_redirs(quote_split(str));
	command->type = command;
	command->next = NULL;
	return (command);
}


void	add_next_cmd(t_cmd *head, t_cmd *new) /* HAY QUE REVISARLO*/
{
	t_cmd	*node;

	node = head;
	if (!node)
		node = new;
	while (node)
		node = node->next;
	node->next = new;
}
/*
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
*/