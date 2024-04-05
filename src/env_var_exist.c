#include "../header/minishell.h"

int	var_exist(t_var_env *env_list, char *var_name)
{
	t_var_env	*tmp;

	tmp = env_list;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->name, var_name) == SUCCESS)
			return (SUCCESS);
		tmp = tmp->next;
	}
	free(tmp);
	return (FAIL);
}
