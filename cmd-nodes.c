/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd-nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:51:09 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/09/06 10:31:16 by crmunoz-         ###   ########.fr       */
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

char **cont_quo_split(char **cmd, char **quote)
{
	char	**totalcmd;
	char	**cmd2;
	int		j;
	int		k;

	j = 0;
	k = 0;
	while (cmd[j])
		j++;
	if (quote[2])
	{
		cmd2 = spliteo_cmd(quote[2], ' ');
		while (cmd2[k])
			k++;
	}
	totalcmd = malloc(sizeof(char *) * (j + k + 1));
	totalcmd = fill_total_cmd(totalcmd, cmd, cmd2, quote);
	return (totalcmd);
}

char	**quote_split(char *str)
{
	char	**quote;
	char	**cmd;
	char	**totalcmd;
	int 	j;
	int		k;

	quote = spliteo_cmd(str, return_quote(str));
	if (quote[0][0] != '\'' && quote[0][0] != '\"')
		cmd = spliteo_cmd(quote[0], ' ');
	else
		cmd = ft_split(quote[0], '\0');
	if (!quote[1])
		return (cmd);
	else
		totalcmd = cont_quo_split(cmd, quote);
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
			break;
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

void	add_next_cmd(t_cmd *head, t_cmd *new)
{
	t_cmd	*node;
	t_cmd	*aux;

	node = head;
	if (!node)
		node = new;
	else
	{
		while (node)
		{
			aux = node;
			node = node->next;
		}
		node = new;
		new->prev = aux;
	}
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
