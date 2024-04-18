#include "../header/minishell.h"

int	is_valid_char(char c)
{
	if (is_digit(c) == FAIL && is_alpha(c) == FAIL && c != '_')
		return (FAIL);
	return (SUCCESS);
}

int	has_env_var(char *token)
{
	int	i;

	i = 0;
	while (token && token[i])
	{
		if (token[i] == '$' && token[i + 1] && \
			(is_valid_char(token[i + 1]) == SUCCESS || token[i + 1] == '?'))
			return (SUCCESS);
		if (token[i] == '$' && token[i + 1] && (token[i + 1] == '"' || \
			token[i + 1] == '\''))
			return (SUCCESS);
		i++;
	}
	return (FAIL);
}

int	check_env_var(t_node **node_tab, int size, t_var_env **env_l, t_data *data)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (i < size)
	{
		if ((*node_tab)[i].token != NULL && \
			(is_str_double_quoted((*node_tab)[i]) == SUCCESS || \
			is_str((*node_tab)[i]) == SUCCESS) && \
			has_env_var((*node_tab)[i].token) == SUCCESS)
		{
			if ((i - 1) >= 0 && (*node_tab)[i - 1].token && \
				(*node_tab)[i - 1].type == T_HEREDOC)
				return (FAIL);
			result += expand_or_empty(node_tab, i, env_l, data);
		}
		i++;
	}
	if (result > 0)
		return (FAIL);
	return (SUCCESS);
}
