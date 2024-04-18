#include "../header/minishell.h"

char	*get_name_env_var(t_node **node_tab, int index)
{
	int	start;
	int	i;

	start = 0;
	i = 0;
	while ((*node_tab)[index].token[i] && (*node_tab)[index].token[i] != '$')
		i++;
	i++;
	start = i;
	if ((*node_tab)[index].token[i] && \
		is_digit((*node_tab)[index].token[i]) == SUCCESS)
		return (ft_strdup((*node_tab)[index].token, start, i + 1));
	if ((*node_tab)[index].token[i] && ((*node_tab)[index].token[i] == '"' || \
		(*node_tab)[index].token[i] == '\''))
		return ("");
	if ((*node_tab)[index].token[i] && (*node_tab)[index].token[i] == '?')
		return (ft_strdup((*node_tab)[index].token, start, i + 1));
	while ((*node_tab)[index].token[i] && \
			is_valid_char((*node_tab)[index].token[i]) == SUCCESS)
		i++;
	return (ft_strdup((*node_tab)[index].token, start, i));
}

int	sub_expand(char *name, int i, t_var_env **env_l, t_node **node_tab)
{
	int		replace_space;
	char	*value;

	value = NULL;
	replace_space = ft_strlen(name) + 1;
	if (var_exist(*env_l, name) == FAIL)
		expand_var(node_tab, i, "\0", replace_space);
	else
	{
		value = take_value(*env_l, name);
		if (!value)
			return (FAIL);
		expand_var(node_tab, i, value, replace_space);
	}
	return (free(value), SUCCESS);
}

int	end_expand(t_node **node_tab, int i, t_var_env **env_l, t_data *data)
{
	if (i - 1 >= 0 && (*node_tab)[i - 1].token && \
		(*node_tab)[i - 1].type == T_HEREDOC)
		return (FAIL);
	return (expand_or_empty(node_tab, i, env_l, data));
}

int	expand_or_empty(t_node **node_tab, int i, t_var_env **env_l, t_data *data)
{
	char	*name;
	char	*value;

	value = NULL;
	name = NULL;
	name = get_name_env_var(node_tab, i);
	if (!name)
		return (FAIL);
	if (name[0] == '?')
	{
		value = ft_itoa(data->ret);
		expand_var(node_tab, i, value, 2);
	}
	else if (sub_expand(name, i, env_l, node_tab) == FAIL)
		return (free(name), FAIL);
	free(value);
	if (name && ft_strlen(name) > 0)
		free(name);
	if (has_env_var((*node_tab)[i].token) == SUCCESS)
		return (end_expand(node_tab, i, env_l, data));
	return (SUCCESS);
}
