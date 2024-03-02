#include "../header/minishell.h"

int	is_str_double_quoted(t_node node)
{
	int	i;

	i = 0;
	if (node.type != T_STR)
		return (FAIL);
	while (node.token[i])
	{
		if (node.token[i] == '"')
			return (SUCCESS);
		i++;
	}
	return (FAIL);
}

int	is_str_single_quoted(t_node node)
{
	int	i;

	i = 0;
	if (node.type != T_STR)
		return (FAIL);
	while (node.token[i])
	{
		if (node.token[i] == '\'')
			return (SUCCESS);
		i++;
	}
	return (FAIL);
}

int	is_str(t_node node)
{
	if (node.type != T_STR)
		return (FAIL);
	if (is_str_double_quoted(node) == FAIL && \
		is_str_single_quoted(node) == FAIL)
		return (SUCCESS);
	return (FAIL);
}

int	is_redir_node(t_node node)
{
	if (!node.type)
		return (FAIL);
	if (node.type == T_STR || node.type == T_PIPE || node.type == T_ERROR)
		return (FAIL);
	return (SUCCESS);
}

int	is_heredoc_node(t_node node)
{
	if (node.type == T_HEREDOC)
		return (SUCCESS);
	return (FAIL);
}
