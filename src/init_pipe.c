#include "../header/minishell.h"

static int	init_pipefd(t_data *data, int (**pipefd)[2])
{
	int	j;

	j = 0;
	if ((*data).nb_pipe > 0)
	{
		*pipefd = (int (*)[2]) malloc((((*data).nb_cmd - 1) * 2) * sizeof(int));
		if (!*pipefd)
			return (FAIL);
		while (j < ((*data).nb_cmd - 1))
		{
			if (pipe((*pipefd)[j]) == -1)
			{
				perror("pipe");
				return (FAIL);
			}
			j++;
		}
	}
	return (SUCCESS);
}

int	start_handle_pipe(t_data *data, int (**pipefd)[2])
{
	if (init_pipefd(data, pipefd) == FAIL)
		return (FAIL);
	(*data).input_fd = STDIN_FILENO;
	return (SUCCESS);
}

void	init_pipe_data(int *i, char **path, char ***result, int (**pipefd)[2])
{
	*i = 0;
	*path = NULL;
	*result = NULL;
	*pipefd = NULL;
}
