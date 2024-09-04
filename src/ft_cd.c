#include "../header/minishell.h"

static int	cd_error(char *str)
{
	ft_putstr_fd("minishell: cd: ", STDERR);
	ft_putstr_fd(str, STDERR);
	ft_putstr_nl_fd(": No such file or directory", STDERR);
	return (FAIL);
}

static void	sub_update_pwd(char *name, char *value, t_data *data)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strjoin_classic(name, value);
	append_list(data, tmp);
	free(tmp);
	tmp = NULL;
}

static int	update_pwd(t_data *data, char *old_pwd)
{
	char	*new_pwd;

	new_pwd = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!new_pwd)
		return (FAIL);
	if (getcwd(new_pwd, BUFFER_SIZE) == NULL)
		return (free(new_pwd), FAIL);
	if (var_exist(data->env_list, "OLDPWD") == SUCCESS)
		udpate_env_var_value(data, "OLDPWD", old_pwd);
	else
		sub_update_pwd("OLDPWD=", old_pwd, data);
	if (var_exist(data->env_list, "PWD") == SUCCESS)
		udpate_env_var_value(data, "PWD", new_pwd);
	else
		sub_update_pwd("PWD=", new_pwd, data);
	return (free(new_pwd), free(old_pwd), SUCCESS);
}

int	sub_cd(t_data *data, char *old_pwd)
{
	char	*home;

	if (var_exist(data->env_list, "HOME") == SUCCESS)
	{
		home = take_value(data->env_list, "HOME");
		if (chdir(home) != 0)
			return (free(old_pwd), cd_error(home));
		return (free(home), update_pwd(data, old_pwd));
	}
	else
	{
		ft_putstr_nl_fd("minishell: cd: \" HOME \" undefined", STDERR);
		return (free(old_pwd), FAIL);
	}
}

int	ft_cd(t_data *data, char **cmd)
{
	char	*old_pwd;

	if (cmd && ft_strlen_tab(cmd) > 2)
	{
		ft_putstr_nl_fd("minishell: cd: too many arguments", STDERR);
		return (FAIL);
	}
	old_pwd = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!old_pwd)
		return (FAIL);
	if (getcwd(old_pwd, BUFFER_SIZE) == NULL)
		return (free(old_pwd), cd_error(cmd[1]));
	if ((!cmd[1] || cmd[1][0] == '~') && (*data).nb_pipe == 0)
		return (sub_cd(data, old_pwd));
	if ((*data).nb_pipe == 0)
	{
		if (is_valid_option(cmd[0], cmd[1]) == FAIL)
			return (free(old_pwd), MISUSE);
		if (chdir(cmd[1]) != 0 || update_pwd(data, old_pwd) == FAIL)
			return (free(old_pwd), cd_error(cmd[1]));
	}
	else
		free(old_pwd);
	return (SUCCESS);
}
