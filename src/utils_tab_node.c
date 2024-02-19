#include "../header/minishell.h"

int	get_node_id_redir(t_node **node_tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if ((*node_tab)[i].type == T_HEREDOC || \
			(*node_tab)[i].type == T_REDIR_IN || \
			(*node_tab)[i].type == T_REDIR_OUT || \
			(*node_tab)[i].type == T_REDIR_OUT_APPEND)
			return (i);
		i++;
	}
	i = -1;
	return (i);
}

int	get_node_id_pipe(t_node **node_tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if ((*node_tab)[i].type == T_PIPE)
			return (i);
		i++;
	}
	i = -1;
	return (i);
}
