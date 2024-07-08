#include "../header/minishell.h"

void	handle_point(t_data *data, char ***result)
{
	ft_putstr_fd("minishell: ", STDERR);
	if (ft_strcmp((*result)[0], ".") == SUCCESS)
	{
		ft_putstr_nl_fd(".: filename argument required", STDERR);
		(*data).ret = MISUSE;
	}
	if (ft_strcmp((*result)[0], "..") == SUCCESS)
	{
		ft_putstr_nl_fd("..: command not found", STDERR);
		(*data).ret = CMD_NOT_FOUND;
	}
	free_all(*result);
	*result = NULL;
}

void	exit_point(t_data *data, char ***result)
{
	if (ft_strcmp((*result)[0], "exit") == SUCCESS && \
	(*data).last == SUCCESS && ft_strlen_tab(*result) <= 2 && \
	(*data).nb_pipe == 0)
		(*data).exit = SUCCESS;
}

void	init_first_pipe(t_data *data, int (*pipefd)[2], int i)
{
	if ((*data).nb_pipe > 0 && i < (*data).nb_cmd - 1)
		(*data).pipe_0 = pipefd[i][0];
}
