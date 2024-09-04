#include "../header/minishell.h"

int	valid_syntax(char *cmd, int size)
{
	int	i;

	i = 0;
	if (is_alpha(cmd[i]) == FAIL && cmd[i] != '_')
		return (display_error(cmd, "export"), FAIL);
	i++;
	if (size == 0)
		size = ft_strlen(cmd);
	while (cmd[i] && i < size)
	{
		if (i == size - 1 && (cmd[i] == '+' || is_digit(cmd[i]) == SUCCESS || \
			is_alpha(cmd[i]) == SUCCESS))
			i++;
		else if (i != size - 1 && (is_digit(cmd[i]) == SUCCESS || \
				is_alpha(cmd[i]) == SUCCESS || cmd[i] == '_'))
			i++;
		else
			return (display_error(cmd, "export"), FAIL);
	}
	return (SUCCESS);
}

int	append_env_var_value(t_data *data, char *var_name, char *new)
{
	t_var_env	*tmp;

	tmp = data->env_list;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->name, var_name) == SUCCESS)
			break ;
		tmp = tmp->next;
	}
	if (tmp != NULL)
	{
		tmp->value = ft_strjoin_classic(tmp->value, new);
		if (!tmp->value)
			return (free(tmp->value), FAIL);
		return (SUCCESS);
	}
	return (FAIL);
}

void	sub_export(char *cmd, t_data *data, int *fail)
{
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	name = extract_name(cmd);
	if (var_exist(data->env_list, name) == SUCCESS)
	{
		value = extract_value(cmd, name);
		if (value && has_plus_equal(cmd) == FAIL)
			udpate_env_var_value(data, name, value);
		else if (value)
			append_env_var_value(data, name, value);
	}
	else if (append_list(data, cmd) == FAIL)
		(*fail)++;
	free(name);
	free(value);
}

int	ft_export(t_data *data, char **cmd)
{
	int		i;
	int		fail;

	i = 1;
	fail = 0;
	if (!cmd[i])
		return (display_sort_env(data), SUCCESS);
	while (cmd && cmd[i] && (*data).nb_pipe == 0)
	{
		if (valid_syntax(cmd[i], get_index_equal(cmd[i])) == SUCCESS)
		{
			if (get_index_equal(cmd[i]) == 0)
				return (SUCCESS);
			sub_export(cmd[i], data, &fail);
		}
		else
			fail++;
		i++;
	}
	if (fail > 0)
		return (FAIL);
	return (SUCCESS);
}
