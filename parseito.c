/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseito.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:34:42 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/09/05 15:41:02 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\r' || c == '\f')
		return (1);
	else
		return (0);
}

int	close_quote(char *str) // comprobamos si hay comillas y están cerradas. Si falta el cierre devuelve 1.
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	while (str[i])
	{
		while (!quote && ft_isspace(str[i]))
			i++;
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (str[i] == '\\' && str[i + 1] != '\0')
			i++;
		else if (quote && str[i] == quote)
			quote = 0;
		i++;
	}
	if (quote == 0)
		return (0);
	else
		return (1);
}
void	**get_pipe_split(char *str) /*ESTA FUNCIÓN NO LA LLAMAMOS AÚN DESDE NINGÚN SITIO*/
{
	char **nopipe;
	t_cmd	cmd;
	int i;

	i = 0;
	nopipe = ft_split(str, '|');
	while (nopipe[i])
	{
		//add_next_cmd(cmd, create_cmd(nopipe[i]));
		i++;
	}
}

void	save_cmd(char *str)
{
	int		i;
	char	quote;
	t_redir	*redir;

	i = 0;
	redir = NULL;
	quote = '\0';
	while (ft_isspace(str[i]))
		i++;
	while (str[i])
	{
		while ((str[i] != ' ' && str[i] != '\t' && quote != str[i]) || (str[i] == '|' && !quote))
		{
			if (str[i] == '\\')
				i++;
			else if (!quote && (str[i] == '\'' || str[i] == '\"'))
				quote = str[i];
			else if (!quote && (str[i] == '<' || str[i] == '>'))
				add_next_redir(redir, create_redir(str, i));
			else if (str[i] == '|' && !quote)
				//node->type = pipe;
			i++;
		}
		if (str[i] == quote)
			quote = '\0';
		i++;
	}
}

/*Cosas:
1. pasarle la línea (si lo hacemos con & podemos ir recorriendolo desde distintas funciones)
2. Creamos la lista y añadimos nodos (los inicializamos)
3. Miramos si es pipe o no.
	Si es un cmd buscamos las comillas y contamos nº de args para hacer el malloc al cmd y posteriormente en otra función guardarlo por trozos.
4. Si es un redir hacemos otra función para crear los nodos y cambiamos el tipo.

*/
/*###########################################################
##################COSAS A TENER EN CUENTA####################
#############################################################

1. Hay que cambiar los exit que hay en los mallocs y protegerlos y hacer free correctamente.
2. Hay que mirar el caso en el que haya espacios en el redir. (Ej: >>            hola). Debemos saltarnos los espacios para guardarlo.


*/