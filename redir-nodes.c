/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir-nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:43:54 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/11/11 16:07:48 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_redir(char *str)
{
	char	*redir;
	int		i;

	redir = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!redir)
		exit(1);
	i = 0;
	while (str[i])
	{
		redir[i] = str[i];
		i++;
	}
	redir[i] = '\0';
	return (redir);
}

t_redir	*ft_lstlast_redir(t_redir *lst)
{
	t_redir	*node;

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

void	add_next_redir(t_redir **head, t_redir *new)
{
	t_redir	*node;

	node = *head;
	if (!(*head))
		*head = new;
	else
	{
		node = ft_lstlast_redir(*head);
		node->next = new;
	}
}

char	*get_redir_file(char *str)
{
	int		i;
	int		j;
	char	*file;

	i = 0;
	j = 0;
	while (str[i] == '<' || str[i] == '>')
		i++;
	file = malloc(sizeof(char) * ft_strlen(str) - i + 1);
	while (str[i])
	{
		file[j] = str[i];
		i++;
		j++;
	}
	file[j] = '\0';
	return (file);
}

int	get_redir_type(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '>' && str[i + 1] == '>')
		return (OUTT);
	if (str[i] == '<' && str[i + 1] == '<')
		return (INN);
	if (str[i] == '>' && str[i + 1] != '>')
		return (OUT);
	if (str[i] == '<' && str[i + 1] != '<')
		return (IN);
	return (0);
}
//A PARTIR DE AQUÍ HAY QUE PASAR LAS FUNCIONES A OTRO ARCHIVO

t_redir	*init_redir(char *str)
{
	t_redir	*redir;

	redir = NULL;
	redir = malloc(sizeof(t_redir));
	if (!redir)
		exit(1);
	redir->name = get_redir_file(str);
	redir->type = get_redir_type(str);
	redir->fd = -1;
	redir->next = NULL;
	return (redir);
}

t_redir	*get_redirs(char **str)
{
	int		i;
	t_redir	*redirs;
	char	*join;

	redirs = NULL;
	join = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i][0] == '<' || str[i][0] == '>')
		{
			if ((ft_strlen(str[i]) <= 2) && str[i + 1])
			{
				join = ft_strjoin(str[i], str[i + 1]);
				i++;
			}
			else
				join = str_redir(str[i]);
			add_next_redir(&redirs, init_redir(join));
		}
		i++;
	}
	return (redirs);
}
