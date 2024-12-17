/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:36:25 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/12/16 19:46:09 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	last_char(const char *s, int c)
{
	int	last;
	int	i;

	last = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			last = i;
		i++;
	}
	return (last);
}

char	**remove_path(char **cmd)
{
	int		last;
	char	*name;

	last = 0;
	if (cmd[0][0] == '\'' || cmd[0][0] == '\"')
		cmd[0] = ft_substr(cmd[0], 1, ft_strlen(cmd[0]) - 2);
	if (cmd[0][0] == '/')
	{
		last = last_char(cmd[0], '/');
		name = ft_substr(cmd[0], last + 1, ft_strlen(cmd[0]) - last);
		free(cmd[0]);
		cmd[0] = name;
	}
	return (cmd);
}

char	**remove_redirs(char **cmd)
{
	int		i;
	char	**new;
	int		count;
	int		flag;

	count = 0;
	i = 0;
	flag = 0;
	while (cmd[i])
	{
		if ((cmd[i][0] == '<' || cmd[i][0] == '>'))
		{
			if (ft_strlen(cmd[i]) <= 2 &&
				cmd[i][1] != '\0' && cmd[i][1] != '<' && cmd[i][1] != '>')
				flag = 1;
		}
		else if (flag == 0)
			count++;


			/*count--;
			if ((ft_strlen(cmd[i]) <= 2))
				count--;
			if (cmd[i][1] != '\0' && cmd[i][1] != '<' && cmd[i][1] != '>')
				count++;
		}*/
		//count++;
		i++;
	}
	new = create_new_cmd(cmd, count);
	return (new);
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

int	count_len(char *arg)
{
	int	i;
	int	stateq;

	i = 0;
	stateq = 0;
	while (arg[i])
	{
		if (arg[i] == '\\')
			i++;
		else if (arg[i] == '\'' || arg[i] == '\"')
			quote_state(&stateq, arg[i]);
		else if (arg[i] == '$' && stateq != 1)
			break ;
		i++;
	}
	return (i);
}
