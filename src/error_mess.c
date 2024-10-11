#include "../header/minishell.h"

void	display_error(char *cmd, char *builtin)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(builtin, STDERR);
	ft_putstr_fd(": « ", STDERR);
	ft_putstr_fd(cmd, STDERR);
	ft_putstr_nl_fd(" » : invalid identifier", STDERR);
}

void	display_error_dir(char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(cmd, STDERR);
	ft_putstr_nl_fd(": Is a directory", STDERR);
}

int	err_msg(char *error, char *str, int code_error)
{
	if (code_error == 1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(error, STDERR);
		ft_putstr_fd(" ", STDERR);
		ft_putstr_nl_fd(str, STDERR);
		return (FAIL);
	}
	else
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(error, STDERR);
		ft_putstr_fd(CHEVRON1, STDERR);
		if (ft_strlen(str) > 2 && ft_strcmp(str, "newline") != SUCCESS)
			write(2, &str[0], 1);
		else
			ft_putstr_fd(str, STDERR);
		ft_putstr_nl_fd(CHEVRON2, STDERR);
		return (MISUSE);
	}
}
