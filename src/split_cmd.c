#include "../header/minishell.h"

static void	middle_cmd_split(t_node **n_tab, int *n, t_tabint *tab, char *c)
{
	while ((*n_tab)[*n].token[(*tab).i])
	{
		if ((*tab).status == OUT_QUOTE && (*n_tab)[*n].token[(*tab).i + 1] && \
			(*n_tab)[*n].token[(*tab).i + 1] == ' ')
		{
			(*tab).i++;
			break ;
		}
		if ((*n_tab)[*n].token[(*tab).i] == *c)
		{
			(*tab).status = change_status_or_not((*tab).status);
			if ((*tab).status == OUT_QUOTE && \
			(*n_tab)[*n].token[(*tab).i + 1] && \
			(*n_tab)[*n].token[(*tab).i + 1] == ' ')
			{
				(*tab).i++;
				break ;
			}
		}
		else if ((*tab).status == OUT_QUOTE && \
		((*n_tab)[*n].token[(*tab).i] == '\'' || \
		(*n_tab)[*n].token[(*tab).i] == '"'))
			update_quote(c, (*n_tab)[*n].token[(*tab).i], tab);
		(*tab).i++;
	}
}

static void	end_cmd_split(t_node **n_tab, int *node, t_tabint *tab)
{
	(*tab).start = (*tab).i;
	while ((*n_tab)[*node].token[(*tab).i])
	{
		if ((*n_tab)[*node].token[(*tab).i] == '"')
			(*tab).status = change_status_or_not((*tab).status);
		if ((*tab).status == OUT_QUOTE && \
			(*n_tab)[*node].token[(*tab).i] == ' ')
			break ;
		(*tab).i++;
	}
}

static void	mini_loop(t_node **n_tab, t_tabint *tab, int *node)
{
	while ((*n_tab)[*node].token[(*tab).i] && \
			(*n_tab)[*node].token[(*tab).i] == ' ')
		(*tab).i++;
}

static int	sub_cmd_split(t_node **n_tab, char **cmd, t_tabint *tab, int *node)
{
	char	c;

	while ((*n_tab)[*node].token[(*tab).i])
	{
		mini_loop(n_tab, tab, node);
		if (((*n_tab)[*node].token[(*tab).i] == '"' || \
		(*n_tab)[*node].token[(*tab).i] == '\'') && (*tab).status == OUT_QUOTE)
		{
			update_data(&c, (*n_tab)[*node].token[(*tab).i], tab);
			middle_cmd_split(n_tab, node, tab, &c);
			cmd[(*tab).index++] = ft_strdup((*n_tab)[*node].token, \
									(*tab).start, (*tab).i);
			if (!cmd[(*tab).index - 1])
				return (free_all(cmd), FAIL);
		}
		else if ((*n_tab)[*node].token[(*tab).i])
		{
			end_cmd_split(n_tab, node, tab);
			cmd[(*tab).index++] = ft_strdup((*n_tab)[*node].token, \
			(*tab).start, (*tab).i);
			if (!cmd[(*tab).index - 1])
				return (free_all(cmd), FAIL);
		}
	}
	return (SUCCESS);
}

char	**split_cmd(t_data *data, t_node **n_tab)
{
	t_tabint	tab;
	int			n;
	int			size;
	char		**result;

	size = compute_size_cmd(data, data->node_tab);
	if (size < 0)
		return (NULL);
	result = malloc((size + 1) * sizeof(char *));
	if (!result || !n_tab)
		return (NULL);
	init_data_split(&tab, &n, data);
	while (n < data->index && n < data->size)
	{
		if ((*n_tab)[n].type == T_STR && ft_strlen((*n_tab)[n].token) != 0)
		{
			if (sub_cmd_split(n_tab, result, &tab, &n) == FAIL)
				return (NULL);
		}
		n++;
		tab.i = 0;
	}
	result[tab.index] = 0;
	return (result);
}
