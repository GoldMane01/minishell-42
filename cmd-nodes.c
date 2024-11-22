/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd-nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:51:09 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/11/11 15:46:29 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	return_quote(char *str)
{
	int		i;
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

char	**add_cmd2(char **totalcmd, char **cmd2, char **quote, int *j)
{
	int	k;
	int	i;

	k = 0;
	if (quote[2])
	{
		while (cmd2[k])
		{
			totalcmd[*j] = malloc((sizeof(char) * (ft_strlen(cmd2[k] + 1))));
			if (!totalcmd[*j])
				free_ptr(totalcmd);
			i = 0;
			while (cmd2[k][i])
			{
				totalcmd[*j][i] = cmd2[k][i];
				i++;
			}
			totalcmd[*j][i] = '\0';
			k++;
			j++;
		}
	}
	return (totalcmd);
}

char	**add_cmd1(char **totalcmd, char **cmd, int *j)
{
	int	i;

	while (cmd[*j])
	{
		totalcmd[*j] = malloc((sizeof(char) * (ft_strlen(cmd[*j] + 1))));
		if (!totalcmd[*j])
			free_ptr(totalcmd);
		i = 0;
		while (cmd[*j][i])
		{
			totalcmd[*j][i] = cmd[*j][i];
			i++;
		}
		totalcmd[*j][i] = '\0';
		*j = *j + 1;
	}
	return (totalcmd);
}

char	**fill_total_cmd(char **totalcmd, char **cmd, char **cmd2, char **quote)
{
	int	j;
	int	i;

	j = 0;
	totalcmd = add_cmd1(totalcmd, cmd, &j);
	if (quote[1])
	{
		totalcmd[j] = malloc((sizeof(char) * (ft_strlen(quote[1] + 1))));
		if (!totalcmd[j])
			free_ptr(totalcmd);
	}
	i = 0;
	while (quote[1][i])
	{
		totalcmd[j][i] = quote[1][i];
		i++;
	}
	totalcmd[j][i] = '\0';
	j++;
	totalcmd = add_cmd2(totalcmd, cmd2, quote, &j);
	totalcmd[++j] = NULL;
	return (totalcmd);
}

char	**create_new_cmd(char **cmd, int count)
{
	char	**new;
	int		i;
	int		j;
	int		k;

	new = malloc(sizeof(char *) * (count + 1));
	if (!new)
		return (NULL);
	i = 0;
	k = 0;
	while (cmd[i])
	{
		while (cmd[i] && (cmd[i][0] == '<' || cmd[i][0] == '>'))
		{
			i++;
			if (ft_strlen(cmd[i - 1]) <= 2)
				i++;
		}
		if (!cmd[i])
			break ;
		new[k] = malloc(sizeof(char) * (ft_strlen(cmd[i]) + 1));
		if (!new[k])
			free_ptr(new);
		j = 0;
		while (cmd[i][j])
		{
			new[k][j] = cmd[i][j];
			j++;
		}
		new[k][j] = '\0';
		i++;
		k++;
	}
	new[k] = NULL;
	return (new);
}

//DESDE AQUÍ HACIA ABAJO HAY QUE CAMBIAR LAS FUNCIONES A OTRO ARCHIVO
char	**remove_redirs(char **cmd)
{
	int		i;
	char	**new;
	int		count;

	count = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '<' || cmd[i][0] == '>')
		{
			count--;
			if ((ft_strlen(cmd[i]) <= 2))
				count--;
			if (cmd[i][1] != '\0' && cmd[i][1] != '<' && cmd[i][1] != '>')
				count++;
		}
		count++;
		i++;
	}
	new = create_new_cmd(cmd, count);
	return (new);
}

t_cmd	*ft_lstlast(t_cmd *lst)
{
	t_cmd	*node;

	node = lst;
	while (node)
	{
		if (node->next)
			node = node->next;
		else
			break ;
	}
	return (node);
}

t_cmd	*add_next_cmd(t_cmd **head, t_cmd *new, t_redir *redirs)
{
	t_cmd	*node;

	node = *head;
	new->redir = redirs;
	if (!(*head))
		*head = new;
	else
	{
		node = ft_lstlast(*head);
		node->next = new;
		node->next->prev = node;
	}
	return (*head);
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

t_cmd	*init_cmd(char **cmd, int type, t_env *env)
{
	t_cmd	*command;

	command = NULL;
	command = malloc(sizeof(t_cmd));
	if (!command)
		exit(1);
	if (type != PIPE)
	{
		command->cmd = cmd;
		command->env = env;
	}
	else
		command->cmd = NULL;
	command->type = type;
	command->next = NULL;
	command->path = NULL;
	command->prev = NULL;
	command->redir = NULL;
	return (command);
}

t_cmd	*add_next_pipe(t_cmd **head)
{
	t_cmd	*command;
	t_cmd	*node;

	node = *head;
	node = ft_lstlast(*head);
	command = NULL;
	command = malloc(sizeof(t_cmd));
	if (!command)
		exit(1);
	command->cmd = NULL;
	command->type = PIPE;
	command->next = NULL;
	command->prev = node;
	command->redir = NULL;
	node->next = command;
	return (command);
}
