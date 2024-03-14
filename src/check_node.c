#include "../header/minishell.h"

static void	error_return(char *cmd, t_data *data)
{
	if (ft_strcmp(cmd, "|") == SUCCESS)
		(*data).ret = err_msg(SYNTAX_ERROR, cmd, 2);
	else
		(*data).ret = err_msg(SYNTAX_ERROR, "newline", 2);
}

static int	check_close_quote(char *cmd)
{
	if (check_unclosed_single(cmd) == FAIL)
		return (FAIL);
	if (check_unclosed_double(cmd) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int	check_error_node(t_node **node_tab, int size, t_data *data)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if ((*node_tab)[i].type == T_ERROR && \
			check_close_quote((*node_tab)[i].token) == FAIL)
		{
			(*data).ret = err_msg(UNCLOSED_ERROR, (*node_tab)[i].token, 1);
			return (FAIL);
		}
		else if ((*node_tab)[i].type == T_ERROR && (i + 1) == size && \
				ft_strlen((*node_tab)[i].token) <= 2)
			return (error_return((*node_tab)[i].token, data), \
					clean_node_error(node_tab, size), FAIL);
		else if ((*node_tab)[i].type == T_ERROR)
		{
			(*data).ret = err_msg(SYNTAX_ERROR, (*node_tab)[i].token, 2);
			return (clean_node_error(node_tab, size), FAIL);
		}
		i++;
	}
	return (SUCCESS);
}

void	check_redir_node(t_node **node_tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (is_redir_node((*node_tab)[i]) == SUCCESS)
		{
			if ((i + 1) == size)
			{
				(*node_tab)[i].type = T_ERROR;
				return ;
			}
			if ((*node_tab)[i + 1].type == T_HEREDOC || \
				(*node_tab)[i + 1].type == T_REDIR_IN || \
				(*node_tab)[i + 1].type == T_REDIR_OUT || \
				(*node_tab)[i + 1].type == T_REDIR_OUT_APPEND || \
				(*node_tab)[i + 1].type == T_PIPE)
			{
				(*node_tab)[i].type = T_ERROR;
				return ;
			}
		}
		i++;
	}
}

void	check_pipe_node(t_node **node_tab, int size)
{
	const int	redir_id = get_node_id_pipe(node_tab, size);

	if (redir_id >= 0)
	{
		if (redir_id - 1 < 0)
		{
			(*node_tab)[redir_id].type = T_ERROR;
			return ;
		}
		if ((redir_id + 1) == size)
		{
			(*node_tab)[redir_id].type = T_ERROR;
			return ;
		}
		if ((*node_tab)[redir_id + 1].type == T_PIPE)
		{
			(*node_tab)[redir_id].type = T_ERROR;
			return ;
		}
	}
}
