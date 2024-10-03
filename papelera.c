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

