/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:23:41 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/09/09 19:52:13 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stddef.h>

typedef enum s_type
{
	PIPE,
	COMMAND,
	BUILD,
	IN,
	INN,
	OUT,
	OUTT
}			t_type;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_redir
{
	char			*name;
	int				type;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**cmd;
	int				type;
	struct s_redir	*redir;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;

//ENV
char	*get_env_key(char *env);
char	*get_env_value(char *env);
t_env	*new_env(char *key_data, char *val_data);
void	add_env(t_env *head, t_env *new);
t_env	*create_env(char **env);

//PARSEITO
int		ft_isspace(char c);
int		close_quote(char *str);
void	save_cmd(char *str);
void	**get_pipe_split(char *str);
char 	**split_pipe(char *str);

//JOIN
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);

//REDIR-NODES
void	add_next_redir(t_redir *head, t_redir *new);

//REDIR
char	*get_redir_file(char *file, int i, int type);
t_redir	*init_redir(char *file, int i, int type);
t_redir	*create_redir(char *line, int i);

//CMD-NODES
int		count_pipes(t_cmd *cmd);
char	**quote_split(char *str);
char	return_quote(char *str);

t_cmd	*add_next_cmd(t_cmd **head, t_cmd *new);
char	*ft_strchr(const char *s, int c);

//SPLIT
size_t	count_strs(char const *s, char c);
char	**free_ptr(char	**ptr);
char	**ft_split(char const *s, char c);
char	*ft_strdup(char *s1);
void	free_arrays(char **awks, char **flags);
char	*ft_substr(char const *s, unsigned int start, size_t len);

//SPLITEO
char	**spliteo_cmd(char *s, char c);

char	**args_split(char *cmd);
char	**remove_redirs(char **cmd);


t_cmd	*init_cmd(char **cmd, int type);