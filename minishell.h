/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:23:41 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/12/05 17:31:22 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stddef.h>
#include <fcntl.h>
#include <limits.h>
#include <linux/limits.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

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
	int				fd;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**cmd;
	int				type;
	char			*path;
	struct s_redir	*redir;
	struct s_env	*env;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;

//ENV
char	*set_env_key(char *env);
char	*set_env_value(char *env);
t_env	*new_env(char *key_data, char *val_data);
void	add_env(t_env *head, t_env *new);
t_env	*create_env(char **env);
char	*get_env_value(char *key, t_env *head);

//PARSEITO
int		ft_isspace(char c);
int		close_quote(char *str);
int		get_n_pipe(char *str);
char	**split_pipe(char *str);

//JOIN
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_isalun(char c);
int		ft_strcmp(char *s1, char *s2);

//REDIR-NODES
char	*get_redir_file(char *file);
void	add_next_redir(t_redir **head, t_redir *new);
t_redir	*init_redir(char *file);
t_redir	*get_redirs(char **str);
//t_redir	*create_redir(char *line, int i);

//CMD-NODES
char	return_quote(char *str);
char	**add_cmd1(char **totalcmd, char **cmd, int *j);
char	**fill_total_cmd(char **totalcmd, char **cmd,
			char **cmd2, char **quote);
char	**create_new_cmd(char **cmd, int count);
char	**remove_redirs(char **cmd);
char	*ft_strchr(const char *s, int c);
t_cmd	*add_next_pipe(t_cmd **head);
t_cmd	*add_next_cmd(t_cmd **head, t_cmd *new, t_redir *redirs);

//SPLIT
size_t	count_strs(char const *s, char c);
char	**free_ptr(char	**ptr);
char	**ft_split(char const *s, char c);
char	*ft_strdup(char *s1);
char	*ft_substr(char const *s, int start, int len);

//SPLITEO
size_t	n_str(char *s, char c);
char	**spliteo_cmd(char *s, char c);

char	**args_split(char *cmd);
char	**remove_redirs(char **cmd);

t_cmd	*init_cmd(char **cmd, int type, t_env *env);

t_cmd	*ft_lstlast(t_cmd *lst);

/* PARSING */
void	quote_state(int *state, char c);

/* EXPAND ARG*/
char	*expand_arg(char *arg, t_env *env);
char	*expand_all(char *arg, t_env *env);

/* BUILTINS */
void	print_env(t_env *env);
void	ft_export(t_env *env, char **cmd);
int		ft_unset(t_env	**env, char	*key);
void	ft_echo(char **cmd);
void	ft_pwd(void);
int		ft_cd(char **cmd);
void	ft_exit(char **cmd);
int		ft_builtins_nopipe(t_env *env, t_cmd *cmd);
int		ft_builtins_pipe(t_env *env, t_cmd *cmd);
int		is_builtin(char *cmd);
int		is_builtin_nopipe(char *cmd);

/* PIPEX */
void	pipex(t_cmd **cmd, char **env);
//void	execute(t_cmd *cmd, t_redir *fdin, t_redir *fdout, int fd[]);
t_redir	*get_fd_in(t_cmd *cmd);
t_redir	*get_fd_out(t_cmd *cmd);

/* REMOVE QUOTES */
char	*remove_quote(char *str);
void	process_quotes(t_cmd *command);