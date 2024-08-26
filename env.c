#include "minishell.h"

char	*get_env_key(char *env)
{
	char	*key;
	int		i;
	
	i = 0;
	while (env[i] != '=')
		i++;
	key = malloc(sizeof(char) * (i));
	i = -1;
	while (env[++i] != '=')
		key[i] = env[i];
	key[i] = '\0';
	return (key);
}

char	*get_env_value(char *env)
{
	char	*value;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	while (env[i] != '=')
		i++;
	while (env[j + i + 1])
		j++;
	value = malloc(sizeof(char) * (j));
	j = 0;
	while (env[i + 1])
	{
		value[j] = env[i + 1];
		j++;
		i++;
	}
	value[j] = '\0';
	return (value);
}

t_env	*new_env(char *key_data, char *val_data)
{
	t_env	*env_node;

	env_node = malloc(sizeof(t_env));
	if (env_node == NULL)
		exit(1);
	env_node->key = key_data;
	env_node->value = val_data;
	env_node->next = NULL;
	return (env_node);
}

void	add_env(t_env *head, t_env *new)
{
	t_env	*aux;

	aux = head;
	while (aux->next)
		aux = aux->next;
	aux->next = new;
}

t_env	*create_env(char **env)
{
	t_env	*struct_env;
	int		i;

	i = 1;
	struct_env = new_env(get_env_key(env[0]), get_env_value(env[0]));
	while (env[i])
	{
		add_env(struct_env, new_env(get_env_key(env[i]), get_env_value(env[i])));
		i++;
	}
	return (struct_env);
}
