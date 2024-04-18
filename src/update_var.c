#include "../header/minishell.h"

void	update_data(char *c, char value, t_tabint *tab)
{
	*c = value;
	(*tab).start = (*tab).i;
	(*tab).i++;
	(*tab).status = change_status_or_not((*tab).status);
}

void	update_param(t_quote *quote, char value)
{
	(*quote).value = value;
	(*quote).status = change_status_or_not(quote->status);
}

void	update_quote(char *c, char value, t_tabint *tab)
{
	*c = value;
	(*tab).status = change_status_or_not((*tab).status);
}

int	udpate_env_var_value(t_data *data, char *var_name, char *new)
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
		free(tmp->value);
		tmp->value = ft_strdup(new, 0, ft_strlen(new));
		if (!tmp->value)
			return (FAIL);
		return (SUCCESS);
	}
	return (FAIL);
}
