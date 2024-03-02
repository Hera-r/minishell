#include "../header/minishell.h"

int	sub_lexer(char **cmd_tab, t_node **node_tab, int *i, int *index)
{
	if (cmd_tab[*i][0] == '|')
	{
		(*node_tab)[(*index)++] = check_pipe(cmd_tab[*i]);
		if (!(*node_tab)[*(index) - 1].token)
			return (FAIL);
	}
	else if (cmd_tab[*i][0] == '>' || cmd_tab[*i][0] == '<')
	{
		(*node_tab)[(*index)++] = check_redir(cmd_tab[*i]);
		if (!(*node_tab)[(*index) - 1].token)
			return (FAIL);
	}
	else
	{
		(*node_tab)[(*index)++] = check_str(cmd_tab[*i]);
		if (!(*node_tab)[(*index) - 1].token)
			return (FAIL);
	}
	(*i)++;
	return (SUCCESS);
}

void	free_node_t(t_node **node_tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (*node_tab && node_tab[i])
		{
			free(node_tab[i]->token);
			node_tab[i]->token = NULL;
			free(node_tab[i]);
			node_tab[i] = NULL;
		}
		i++;
	}
	if (*node_tab)
	{
		free(*node_tab);
		*node_tab = NULL;
	}
}

void	free_simple_node(t_node *node_tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (node_tab[i].token)
		{
			free(node_tab[i].token);
			node_tab[i].token = NULL;
		}
		i++;
	}
	if (node_tab)
	{
		free(node_tab);
		node_tab = NULL;
	}
}

t_node	*lexer(char **cmd_tab)
{
	int		i;
	int		index;
	t_node	*node_tab;

	i = 0;
	index = 0;
	node_tab = malloc(ft_strlen_tab(cmd_tab) * sizeof(t_node));
	if (!node_tab)
		return (NULL);
	while (cmd_tab && cmd_tab[i])
	{
		if (sub_lexer(cmd_tab, &node_tab, &i, &index) == FAIL)
			return (free_node_t(&node_tab, ft_strlen_tab(cmd_tab)), NULL);
	}
	return (node_tab);
}
/*
sécuriser le malloc du node_tab + 
ft_strdup en créant une fonction qui free le node_tab
*/