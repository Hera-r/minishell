#include "../header/minishell.h"

void	reset_signal(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

void	append_pid(t_data *data, pid_t pid)
{
	t_child_pid	*new_elem;
	t_child_pid	*tmp;

	new_elem = malloc(sizeof(t_child_pid));
	if (!new_elem)
		return ;
	new_elem->pid = pid;
	new_elem->next = NULL;
	if (data->pid_list == NULL)
		data->pid_list = new_elem;
	else
	{
		tmp = data->pid_list;
		while (tmp && tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_elem;
	}
}

static void	free_path(char *path, char *args)
{
	if (ft_strcmp(path, args) != SUCCESS)
		free(path);
}

void	sub_exec(t_data *data)
{
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
}

int	exec_cmd(char *path, char **args, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork failed"), exit(EXIT_FAILURE), FAIL);
	append_pid(data, pid);
	if (pid == 0)
	{
		sub_exec(data);
		reset_signal();
		if ((*data).pipe_0 > 0)
			close((*data).pipe_0);
		if (execve(path, args, data->env_tab) == -1)
			perror(path);
	}
	return (free_path(path, args[0]), SUCCESS);
}
