#include "../header/minishell.h"

int	is_dir_or_cmdnotfound(char *path)
{
	if (is_directory(path) == SUCCESS)
		return (PERM_DENY);
	return (CMD_NOT_FOUND);
}

int	is_empty_cmd(char *cmd)
{
	if (ft_strcmp(cmd, "\"\"") == SUCCESS || ft_strcmp(cmd, "") == SUCCESS || \
		ft_strcmp(cmd, "''") == SUCCESS || ft_strcmp(cmd, " ") == SUCCESS)
		return (SUCCESS);
	return (FAIL);
}

void	end_pipeline(t_data *data, int (*pipefd)[2])
{
	t_child_pid	*tmp;
	int			status;

	tmp = data->pid_list;
	status = 0;
	while (tmp != NULL)
	{
		if (waitpid(tmp->pid, &status, 0) == tmp->pid)
			tmp = tmp->next;
	}
	if (WIFEXITED(status) && (*data).ret == 0)
		(*data).ret = WEXITSTATUS(status);
	if ((*data).nb_pipe > 0)
		free(pipefd);
	free_pid_list(data->pid_list);
	data->pid_list = NULL;
	if ((*data->node_tab) != NULL)
	{
		free_simple_node((*data->node_tab), (*data).size);
		data->node_tab = NULL;
	}
	if ((*data).input_fd != STDIN)
		close((*data).input_fd);
	if ((*data).output_fd != STDOUT && (*data).output_fd > 0)
		close((*data).output_fd);
}

void	clean_pipeline(t_data *data, char ***result, int (*pipefd)[2])
{
	int	i;

	i = 0;
	free_all(*result);
	*result = NULL;
	while (i < (*data).nb_cmd - 1)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
	end_pipeline(data, pipefd);
}

int	handle_pipeline(t_data *data)
{
	int		(*pipefd)[2];
	int		i;
	char	*path;
	char	**result;

	init_pipe_data(&i, &path, &result, &pipefd);
	if (start_handle_pipe(data, &pipefd) == FAIL)
		return (FAIL);
	while (i < (*data).nb_cmd)
	{
		signal(SIGINT, SIG_IGN);
		if (sub_again_pipe(data, &result, &i, pipefd) == FAIL)
			break ;
		if (result[0] && data->input_fd >= 0 && data->output_fd > 0)
		{
			init_first_pipe(data, pipefd, i);
			if (is_empty_cmd(result[0]) == SUCCESS)
				empty_cmd(data);
			else
				sub_else_pipe(data, &result, &path, pipefd);
		}
		end_loop_pipe(data, &result, &i, pipefd);
		i++;
	}
	return (clean_pipeline(data, &result, pipefd), SUCCESS);
}
