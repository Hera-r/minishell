#include "../header/minishell.h"

void	free_all(char **content)
{
	int	i;

	i = 0;
	while (content && content[i])
	{
		if (content[i])
		{
			free(content[i]);
			content[i] = NULL;
		}
		i++;
	}
	if (content)
	{
		free(content);
		content = NULL;
	}
}

void	free_pid_list(t_child_pid *pid_list)
{
	t_child_pid	*tmp;

	while (pid_list && pid_list->next != NULL)
	{
		tmp = pid_list->next;
		free(pid_list);
		pid_list = NULL;
		pid_list = tmp;
	}
	if (pid_list)
	{
		free(pid_list);
		pid_list = NULL;
	}
}

void	free_node_tab(t_data *data)
{
	int	i;

	i = 0;
	if (!*data->node_tab)
		return ;
	while (i < (*data).size)
	{
		if ((*data->node_tab)[i].token)
			free((*data->node_tab)[i].token);
		i++;
	}
	free(*data->node_tab);
	*data->node_tab = NULL;
}

void	free_env_list(t_data *data)
{
	t_var_env	*tmp;

	while (data->env_list != NULL)
	{
		tmp = data->env_list->next;
		free(data->env_list->name);
		free(data->env_list->value);
		free(data->env_list);
		data->env_list = NULL;
		data->env_list = tmp;
	}
	if (data->env_list)
	{
		free(data->env_list);
		data->env_list = NULL;
	}
}

void	free_pipefd(int (*pipefd)[2], int size)
{
	if (size > 0)
		free(pipefd);
	pipefd = NULL;
}
