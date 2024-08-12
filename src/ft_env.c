#include "../header/minishell.h"

int	ft_env(t_data *data, char **cmd)
{
	if (cmd[1] && ft_strcmp(cmd[1], "env") != SUCCESS)
	{
		if (cmd[1][0] == '-' && !cmd[1][1])
			exit(SUCCESS);
		else if (cmd[1][0] == '-' && cmd[1][1])
		{
			is_valid_option(cmd[0], cmd[1]);
			exit(MISUSE);
		}
		ft_putstr_fd("env: ", STDERR);
		ft_putstr_fd(cmd[1], STDERR);
		ft_putstr_nl_fd(": No such file or directory", STDERR);
		exit(CMD_NOT_FOUND);
	}
	display_env_list(data->env_list);
	return (SUCCESS);
}
