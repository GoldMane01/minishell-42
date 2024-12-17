/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:23:41 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/12/17 16:50:34 by crmunoz-         ###   ########.fr       */
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

typedef struct s_fd
{
	t_redir		*fdin;
	t_redir		*fdout;
}				t_fd;

typedef struct s_cmd
{
	char			**cmd;
	int				type;
	char			*path;
	int				status;
	struct s_redir	*redir;
	struct s_env	*env;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;

//LIB
int			ft_isalun(char c);
int			ft_isdigit(char *str);
int			ft_isspace(char c);
char		*ft_itoa(int n);
t_cmd		*ft_lstlast(t_cmd *lst);
char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *s, int c);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strdup(char *s1);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
int			ft_strlen(const char *s);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_substr(char const *s, int start, int len);
int			ft_lstsize(t_env *lst);

//BUILTINS
void		ft_exporting(t_env *env, char *key, char *value);
void		ft_export(t_env *env, char **cmd);
int			ft_cont_unset(t_env	**current, t_env **temp, char *key);
int			ft_unset(t_env	**env, char	*key);
void		ft_echo(char **cmd);
void		print_env(t_env *env);
void		ft_pwd(void);
int			changedir(char *path);
int			ft_cd(char **cmd);

//CHECK_BUILT
int			is_builtin(char *cmd);
int			is_builtin_nopipe(char *cmd);
int			ft_builtins_pipe(t_env *env, t_cmd *cmd);
int			ft_builtins_nopipe(t_env *env, t_cmd *cmd);

//EXIT
void		print_errexit(char *str);
long		ft_atol(char *str);
void		ft_exit(char **cmd);

//ARGS
int			len_each_arg(char *cmd);
int			args_cnt(char *cmd);
char		**args_split(char *cmd);

//CMD
char		**second_cmd(char **total, char **cmd2, char **quote, int *j);
char		**first_cmd(char **total, char **cmd, int *j);
char		**totalcmd(char **total, char **cmd, char **cmd2, char **quote);
char		**create_new_cmd(char **cmd, int count);
t_cmd		*add_next_cmd(t_cmd **head, t_cmd *new, t_redir *redirs);

//ENV
char		*set_env_key(char *env);
char		*set_env_value(char *env);
void		add_env(t_env *head, t_env *new);
t_env		*create_env(char **env);
char		*get_env_value(char *key, t_env *head);

//EXPAND
char		*get_value(char *arg, t_env *env);
char		*expand_dollar(char *arg, char *value);
char		*change_len(char *arg, char *value);
char		*expand_arg(char *arg, t_env *env, int last_status);
char		*expand_all(char *arg, t_env *env, int last_status);

//FD
int			here_doc_eof(char *line, char *eof);
int			open_here_doc(t_redir *fd);
t_redir		*get_fd_in(t_cmd *cmd);
t_redir		*get_fd_out(t_cmd *cmd);

//FREE
void		free_redir(t_redir *redir);
void		free_cmd(t_cmd *cmd);
char		**free_ptr(char	**ptr);
void		free_env(t_env *env);

//INIT
t_env		*new_env(char *key_data, char *val_data);
t_cmd		*init_cmd(char **cmd, int type, t_env *env);
t_redir		*init_redir(char *str);

//PARSING
char		*concat_quote(char *line, char *quote);
int			get_last_status(t_cmd *cmd);
int			parse_line(char *line, t_env *str_env);

//PATH
int			check_access(char *path, char *command);
char		*get_path(char *path, char *command);
char		*check_paths(char **allpaths, char *command);
char		*cmdpath(t_cmd *cmd);
int			has_path(char **cmd);

//PIPEX
int			execute(t_cmd *cmd, t_fd *fd_pipe, int fd[], int fd_in);
void		pipex(t_cmd **cmd);
void		child_process(t_cmd *cmd, t_fd *fd_pipe, int fd[], int fd_in);

//QUOTES
char		*remove_quote(char *str);
void		process_quotes(t_cmd *command);
int			close_quote(char *str);
char		return_quote(char *str);
void		quote_state(int *state, char c);

//REDIR
char		*str_redir(char *str);
void		add_next_redir(t_redir **head, t_redir *new);
char		*get_redir_file(char *str);
int			get_redir_type(char *str);
t_redir		*get_redirs(char **str);

//SIGNALS
void		ctrl_c_handler(int sig);
void		ctrl_quit_handler(int sig);

//SPLITTING
size_t		n_str(char *s, char c);
char		**split_cmd(char *s, char c);
int			get_n_pipe(char *str);
char		**split_pipe(char *str);

//UTILS
int			last_char(const char *s, int c);
char		**remove_path(char **cmd);
char		**remove_redirs(char **cmd);
t_redir		*ft_lstlast_redir(t_redir *lst);
int			count_len(char *arg);