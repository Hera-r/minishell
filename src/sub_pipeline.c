#include "../header/minishell.h"

static void	sub_pipe(int *i, t_data *data, int (*pipefd)[2])
{
	if (*i == (*data).nb_cmd - 1)
	{
		(*data).last = SUCCESS;
		if ((*data).output_fd != STDOUT_FILENO && (*data).output_fd > 0)
			close((*data).output_fd);
		(*data).output_fd = STDOUT_FILENO;
	}
	else
		(*data).output_fd = pipefd[*i][1];
}

void	end_loop_pipe(t_data *data, char ***result, int *i, int (*pipefd)[2])
{
	if (data->input_fd < 0 || data->output_fd < 0)
	{
		free_all(*result);
		*result = NULL;
	}
	if (ft_strlen_tab(*result) == 0)
	{
		free_all(*result);
		*result = NULL;
	}
	if (*i < (*data).nb_cmd - 1)
	{
		close(pipefd[*i][1]);
		if ((*data).input_fd != STDIN)
			close((*data).input_fd);
		(*data).input_fd = pipefd[*i][0];
	}
}

void	sub_exec_pipe(t_data *data, char ***result, char **path)
{
	*path = process_path((*result)[0], (*data).env_tab);
	if (*path)
		(*data).ret = exec_cmd(*path, *result, data);
	else
		(*data).ret = is_dir_or_cmdnotfound((*result)[0]);
	if ((*data).last == FAIL && *result)
	{
		free_all(*result);
		*result = NULL;
	}
}

void	sub_else_pipe(t_data *data, char ***result, char **path, int (*pfd)[2])
{
	exit_point(data, result);
	if (is_builtin((*result)[0]) == SUCCESS)
	{
		(*data).ret = exec_builtin(data, *result, pfd);
		free_all(*result);
		*result = NULL;
	}
	else if ((ft_strcmp((*result)[0], ":") == SUCCESS || \
			ft_strcmp((*result)[0], "!") == SUCCESS) && \
			ft_strlen((*result)[0]) == 1)
	{
		(*data).ret = SUCCESS;
		free_all(*result);
		*result = NULL;
	}
	else if ((ft_strcmp((*result)[0], ".") == SUCCESS || \
			ft_strcmp((*result)[0], "..") == SUCCESS))
		handle_point(data, result);
	else
		sub_exec_pipe(data, result, path);
}

int	sub_again_pipe(t_data *data, char ***result, int *i, int (*pipefd)[2])
{
	sub_pipe(i, data, pipefd);
	if (count_redir_cmd(data, *(data->node_tab)) > 0 && \
		handle_redir(data, *(data->node_tab), pipefd) == FAIL)
		return (FAIL);
	*result = extract_cmd(data);
	if (*result == NULL)
		return (FAIL);
	return (SUCCESS);
}
