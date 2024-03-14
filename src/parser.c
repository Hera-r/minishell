#include "../header/minishell.h"

int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (SUCCESS);
	return (FAIL);
}

char	*extract_str(t_node node)
{
	int		i;
	int		start;
	int		status;

	i = 0;
	start = 0;
	status = OUT_QUOTE;
	if (node.token[i] && (node.token[i] == '\'' || node.token[i] == '"'))
	{
		i++;
		start = i;
		status = IN_QUOTE;
	}
	while (node.token[i] && ((node.token[i] != ' ' && status == OUT_QUOTE) || \
		((node.token[i] != '"' || node.token[i] != '\'') && \
		status == IN_QUOTE)))
	{
		if ((node.token[i] == '"' || node.token[i] == '\'') && \
			status == IN_QUOTE)
			status = OUT_QUOTE;
		i++;
	}
	if (node.token[i - 1] && is_quote(node.token[i - 1]) == SUCCESS)
		i--;
	return (ft_strdup(node.token, start, i));
}

char	*update_token(t_node **node_tab, int index)
{
	int		i;
	int		j;
	char	*new_token;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = (*node_tab)[index + 1].token;
	new_token = malloc(ft_strlen(tmp) - \
				ft_strlen((*node_tab)[index].token) + 1);
	if (!new_token)
		return (0);
	if (is_quote(tmp[j]) == SUCCESS)
		j++;
	while (tmp[j] && tmp[j++] == (*node_tab)[index].token[i])
		i++;
	while (tmp[j] && tmp[j] == ' ')
		j++;
	i = 0;
	while (tmp[j])
		new_token[i++] = tmp[j++];
	new_token[i] = '\0';
	return (free(tmp), new_token);
}

int	complete_redir_node(t_node **node_tab, int *size)
{
	int	i;

	i = 0;
	while (i < *size)
	{
		if (is_redir_node((*node_tab)[i]) == SUCCESS)
		{
			free((*node_tab)[i].token);
			(*node_tab)[i].token = extract_str((*node_tab)[i + 1]);
			if (!(*node_tab)[i].token)
				return (FAIL);
			(*node_tab)[i + 1].token = update_token(node_tab, i);
			if (!(*node_tab)[i + 1].token)
				return (FAIL);
		}
		i++;
	}
	return (SUCCESS);
}

int	parser(t_node **node_tab, int size, t_var_env **env_list, t_data *data)
{
	check_redir_node(node_tab, size);
	check_pipe_node(node_tab, size);
	if (check_error_node(node_tab, size, data) == FAIL)
		return (FAIL);
	if (check_env_var(node_tab, size, env_list, data) == FAIL)
		return (FAIL);
	if (complete_redir_node(node_tab, &size) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
