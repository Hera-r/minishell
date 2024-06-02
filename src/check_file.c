#include "../header/minishell.h"

void	check_file(char const *file, int i)
{
	if (i == 1)
	{
		if (access(file, R_OK) != 0)
		{
			ft_putstr_fd("minishell : ", STDERR);
			perror(file);
		}
	}
	else
	{
		if (access(file, F_OK) == 0)
		{
			if (access(file, W_OK) != 0)
			{
				ft_putstr_fd("minishell : ", STDERR);
				perror(file);
			}
		}
	}
}
