#include "../header/minishell.h"

void	sub_exec_builtin(t_data *data, int (*pipefd)[2])
{
	int	i;

	if ((*data).input_fd != STDIN_FILENO)
	{
		dup2((*data).input_fd, STDIN_FILENO);
		close((*data).input_fd);
	}
	if ((*data).output_fd != STDOUT_FILENO)
	{
		dup2((*data).output_fd, STDOUT_FILENO);
		close((*data).output_fd);
	}
	if ((*data).pipe_0 > 0)
		close((*data).pipe_0);
	i = 0;
	while (i < data->nb_cmd - 1)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
}

int	exec_builtin(t_data *data, char **args, int (*pipefd)[2])
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (perror("fork failed"), exit(EXIT_FAILURE), FAIL);
	append_pid(data, pid);
	if (pid == 0)
	{
		sub_exec_builtin(data, pipefd);
		status = builtin_list(data, args);
		clean_child(data, args, pipefd);
		exit(status);
	}
	else
		return (builtin_parent(data, args));
	return (SUCCESS);
}
