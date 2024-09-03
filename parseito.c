/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseito.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:34:42 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/09/03 18:14:08 by crmunoz-         ###   ########.fr       */
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

char	**quote_split(char *str) /*-> podemos hacer primero un split por pipe, y luego pasar cada trozo aquí, para hacer el final split */
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

void	save_cmd(char *str)
{
	int		i;
	int		j;
	char	quote;
	t_redir	*redir;

	i = 0;
	redir = NULL;
	quote = '\0';
	while (ft_isspace(str[i]))
		i++;
	j = i;
	while (str[i])
	{
		while ((str[i] != ' ' && str[i] != '\t' && quote != str[i]) || (str[i] == '|' && !quote))
		{
			if (str[i] == '\\')
				i++;
			else if (!quote && (str[i] == '\'' || str[i] == '\"'))
			{
				quote = str[i];
				j = i;
			}
			else if (!quote && (str[i] == '<' || str[i] == '>'))
				add_next_redir(redir, create_redir(str, i));
			else if (str == "|" && !quote)
				//node->type = pipe;
			i++;
		}
		i++;
		if (quote == str[i])
			quote = '\0';
		if (quote == '\0')
		{	
			//node->cmd = (crear funcion para guardar el array)
		}
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