#include "../header/minishell.h"

void	display_env_list(t_var_env *env_list)
{
	t_var_env	*tmp;

	tmp = env_list;
	while (tmp != NULL)
	{
		ft_putstr_fd(tmp->name, STDOUT);
		ft_putstr_fd("=", STDOUT);
		ft_putstr_nl_fd(tmp->value, STDOUT);
		tmp = tmp->next;
	}
	free(tmp);
}
