/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:43:54 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/08/28 19:48:00 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_redir_file(char *file, int i, int type)
{
	char	*name;
	int		j;

	j = 0;
	if (type == INN || type == OUTT)
		i += 2;
	else
		i += 1;
	while (ft_isspace(file[i]))
		i++;
	while (!ft_isspace(file[i++]))
		j++;
	name = malloc(sizeof(char) * (j + 1));
	if (!name)
		exit(1);
	i = i - j - 1;
	j = 0;
	while (!ft_isspace(file[i]))
	{
		name[j] = file[i];
		j++;
		i++;
	}
	name[j] = '\0';
	return (name);
}

t_redir	*init_redir(char *file, int i, int type)
{
	t_redir	*redir;

	redir = malloc(sizeof(redir));
	if (!redir)
		exit(1);
	redir->name = get_redir_file(file, i, type);
	redir->type = type;
	redir->next = NULL;
	return (redir);
}

t_redir	*create_redir(char *line, int i)
{
	if (line[i] == '<' && line[i + 1] == '<')
		return (init_redir(line, i, INN));
	if (line[i] == '<' && line[i + 1] != '<')
		return (init_redir(line, i, IN));
	if (line[i] == '>' && line[i + 1] == '>')
		return (init_redir(line, i, OUTT));
	if (line[i] == '>' && line[i + 1] != '>')
		return (init_redir(line, i, OUT));
	return (NULL);
}
