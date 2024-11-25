#include "minishell.h"

void	free_arrays(char **awks, char **flags)
{
	int	i;

	i = 0;
	if (awks)
	{
		while (awks[i])
		{
			free(awks[i]);
			i++;
		}
		free(awks);
	}
	i = 0;
	if (flags)
	{
		while (flags[i])
		{
			free(flags[i]);
			i++;
		}
		free(flags);
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

int	count_pipes(t_cmd *cmd)
{
	t_cmd	*node;
	int		count;

	node = cmd;
	count = 0;
	if (!node)
		return (0);
	while (node)
	{
		if (node->type == PIPE)
			count++;
		node = node->next;
	}
	return (count);
}

char	**get_cmd(char *file)
{
	int		i;
	char	**cmd;

	i = 0;
	while (file[i] != '|' && file[i] != '\0')
		i++;
	if (file[i] == '|')
		file[i] = '\0';
	cmd = ft_split(file, ' ');
	cmd = remove_redirs(cmd);
	return (cmd);
}

t_cmd *init_cmd(char *file, int i, int j, int type)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(cmd));
	if (!cmd)
		exit(1);
	if (cmd != PIPE)
		//cmd->cmd = get_cmd(file, i, j);
	//else
		cmd->cmd = NULL;
	cmd->type = type;
	cmd->next = NULL;
}

t_cmd	*init_cmd(char *str, int type)
{
	t_cmd	*command;

	command = malloc(sizeof(command));
	if (!command)
		exit(1);
	if (type != PIPE)
		command->cmd = remove_redirs(quote_split(str));
	else
		command->cmd = NULL;
	command->type = type;
	command->next = NULL;
	command->prev = NULL;
	return (command);
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

int is_builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		return (1);
	return (0);
}
