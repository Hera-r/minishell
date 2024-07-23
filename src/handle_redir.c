#include "../header/minishell.h"

int	redir_in(t_node node, t_data *data)
{
	int	new_fd;

	check_file(node.token, 1);
	new_fd = open(node.token, O_RDONLY);
	if (new_fd < 0)
	{
		(*data).ret = FAIL;
		return (FAIL);
	}
	(*data).input_fd = new_fd;
	return (SUCCESS);
}

int	redir_out(t_node node, t_data *data)
{
	int	new_fd;

	check_file(node.token, 0);
	if (node.type == T_REDIR_OUT)
		new_fd = open(node.token, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else
		new_fd = open(node.token, O_WRONLY | O_APPEND | O_CREAT, 0664);
	if (new_fd < 0)
		(*data).ret = FAIL;
	if ((*data).output_fd != STDOUT)
		close((*data).output_fd);
	(*data).output_fd = new_fd;
	return (SUCCESS);
}

int	handle_heredoc(t_node node, t_data *data, int (*pfd)[2])
{
	int	new_fd;

	new_fd = append_heredoc(node.token, data, pfd);
	(*data).input_fd = new_fd;
	if (new_fd < 0)
		(*data).ret = FAIL;
	return (SUCCESS);
}

int	sub_handle_redir(t_data *data, t_node *node_tab, int (*pfd)[2])
{
	if (node_tab[(*data).index].type == T_HEREDOC)
	{
		if (handle_heredoc(node_tab[(*data).index], data, pfd) == FAIL)
			return (FAIL);
	}
	else if (node_tab[(*data).index].type == T_REDIR_IN)
	{
		if (redir_in(node_tab[(*data).index], data) == FAIL)
			return (FAIL);
	}
	else if (node_tab[(*data).index].type == T_REDIR_OUT)
	{
		if (redir_out(node_tab[(*data).index], data) == FAIL)
			return (FAIL);
	}
	else if (node_tab[(*data).index].type == T_REDIR_OUT_APPEND)
	{
		if (redir_out(node_tab[(*data).index], data) == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}

int	handle_redir(t_data *data, t_node *node_tab, int (*pfd)[2])
{
	while ((*data).index < (*data).size && \
			node_tab[(*data).index].type != T_PIPE)
	{
		if (sub_handle_redir(data, node_tab, pfd) == FAIL)
			return (FAIL);
		(*data).index++;
	}
	if ((*data).index < (*data).size && node_tab[(*data).index].type == T_PIPE)
		(*data).index++;
	return (SUCCESS);
}
