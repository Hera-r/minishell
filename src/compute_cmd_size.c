#include "../header/minishell.h"

static void	cs_middle_loop(t_node **tab, int start, int *i, t_quote *quote)
{
	(*i)++;
	while ((*tab)[start].token[*i])
	{
		if ((*quote).status == OUT_QUOTE && (*tab)[start].token[*i + 1] && \
			(*tab)[start].token[*i + 1] == ' ')
		{
			(*i)++;
			break ;
		}
		if ((*tab)[start].token[*i] == (*quote).value)
		{
			(*quote).status = change_status_or_not((*quote).status);
			if ((*quote).status == OUT_QUOTE && \
			(*tab)[start].token[*i + 1] && (*tab)[start].token[*i + 1] == ' ')
			{
				i++;
				break ;
			}
		}
		else if ((*quote).status == OUT_QUOTE && \
		((*tab)[start].token[*i] == '\'' || (*tab)[start].token[*i] == '"'))
			update_param(quote, (*tab)[start].token[*i]);
		(*i)++;
	}
}

static void	cs_end_loop(t_node **node_tab, int start, int *i, t_quote *quote)
{
	while ((*node_tab)[start].token[*i])
	{
		if ((*node_tab)[start].token[*i] == '"')
			(*quote).status = change_status_or_not(quote->status);
		if (quote->status == OUT_QUOTE && (*node_tab)[start].token[*i] == ' ')
		{
			(*i)++;
			break ;
		}
		(*i)++;
	}
}

static void	cs_main_loop(t_node **node_tab, int start, int *i, t_quote *quote)
{
	while ((*node_tab)[start].token[*i])
	{
		while ((*node_tab)[start].token[*i] && \
				(*node_tab)[start].token[*i] == ' ')
			(*i)++;
		if (((*node_tab)[start].token[*i] == '"' || \
		(*node_tab)[start].token[*i] == '\'') && (*quote).status == OUT_QUOTE)
		{
			update_param(quote, (*node_tab)[start].token[*i]);
			(*quote).size++;
			cs_middle_loop(node_tab, start, i, quote);
		}
		else if ((*node_tab)[start].token[*i])
		{
			(*quote).size++;
			cs_end_loop(node_tab, start, i, quote);
		}
	}
}

static void	init_compute_var(int *i, int *start, t_quote *quote, t_data *data)
{
	*i = 0;
	(*quote).size = 0;
	(*quote).status = OUT_QUOTE;
	*start = data->start_cmd;
}

int	compute_size_cmd(t_data *data, t_node **node_tab)
{
	int		start;
	int		i;
	t_quote	quote;

	init_compute_var(&i, &start, &quote, data);
	while (start < data->index && start < data->size)
	{
		if ((*node_tab)[start].type == T_STR && \
			(ft_strlen((*node_tab)[start].token) != 0 || \
			is_empty_cmd((*node_tab)[start].token) == SUCCESS))
		{
			if (is_empty_cmd((*node_tab)[start].token) == SUCCESS && \
				start - 1 >= 0 && is_redir_node((*node_tab)[start - 1]) == FAIL)
				return (empty_cmd(data));
			while ((*node_tab)[start].token[i])
				cs_main_loop(node_tab, start, &i, &quote);
		}
		start++;
		i = 0;
	}
	return (quote.size);
}
