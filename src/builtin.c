#include "../header/minishell.h"

int	is_valid_option(char *builtin, char *cmd)
{
	if (cmd[0] == '-')
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(builtin, STDERR);
		ft_putstr_fd(": ", STDERR);
		write(STDERR, &cmd[0], 1);
		if (cmd[1])
			write(STDERR, &cmd[1], 1);
		ft_putstr_nl_fd(": invalid option", STDERR);
		return (FAIL);
	}
	return (SUCCESS);
}

int	is_builtin(char *cmd)
{
	if (cmd && (ft_strcmp(cmd, "echo") == SUCCESS || \
		ft_strcmp(cmd, "cd") == SUCCESS || \
		ft_strcmp(cmd, "pwd") == SUCCESS || \
		ft_strcmp(cmd, "export") == SUCCESS || \
		ft_strcmp(cmd, "unset") == SUCCESS || \
		ft_strcmp(cmd, "env") == SUCCESS || \
		ft_strcmp(cmd, "exit") == SUCCESS))
		return (SUCCESS);
	return (FAIL);
}

int	builtin_list(t_data *data, char **cmd)
{
	if (ft_strcmp(cmd[0], "echo") == SUCCESS)
		return (ft_echo(cmd));
	if (ft_strcmp(cmd[0], "pwd") == SUCCESS)
		return (ft_pwd(cmd));
	if (ft_strcmp(cmd[0], "env") == SUCCESS)
		ft_env(data, cmd);
	if (ft_strcmp(cmd[0], "exit") == SUCCESS)
		return (ft_exit(data, cmd));
	return (SUCCESS);
}

int	builtin_parent(t_data *data, char **cmd)
{
	if (ft_strcmp(cmd[0], "export") == SUCCESS)
		return (ft_export(data, cmd));
	if (ft_strcmp(cmd[0], "unset") == SUCCESS)
		return (ft_unset(data, cmd));
	if (ft_strcmp(cmd[0], "cd") == SUCCESS)
		return (ft_cd(data, cmd));
	return (SUCCESS);
}
