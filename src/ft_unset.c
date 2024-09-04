#include "../header/minishell.h"

int	ft_unset(t_data *data, char **cmd)
{
	int	i;
	int	fail;

	i = 1;
	fail = 0;
	while (cmd && cmd[i])
	{
		if (is_alpha(cmd[i][0]) == FAIL && cmd[i][0] != '_')
		{
			display_error(cmd[i], "unset");
			fail++;
		}
		else if (var_exist(data->env_list, cmd[i]) == SUCCESS)
			del_env_var(data, cmd[i]);
		i++;
	}
	if (fail > 0)
		return (FAIL);
	return (SUCCESS);
}
