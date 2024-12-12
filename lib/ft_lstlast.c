#include "../minishell.h"

t_cmd	*ft_lstlast(t_cmd *lst)
{
	t_cmd	*node;

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