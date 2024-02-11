#include "../header/minishell.h"

int	compute_size(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str && str[i])
	{
		while (str[i] && is_space(str[i]) == SUCCESS)
			i++;
		if (str[i] && is_space(str[i]) == FAIL)
		{
			size++;
			while (str[i] && is_separators(str[i]) == FAIL)
				i++;
			if (is_separators(str[i]) == SUCCESS)
			{
				i++;
				size++;
			}
		}
	}
	return (size);
}

void	sub_split(char *str, int *i, int *status)
{
	while (str[*i])
	{
		if ((str[*i] == '"' || str[*i] == '\'') && *status == OUT_QUOTE)
			*status = IN_QUOTE;
		else if ((str[*i] == '"' || str[*i] == '\'') && \
				*status == IN_QUOTE)
			*status = OUT_QUOTE;
		else if (is_separators(str[*i]) == SUCCESS && \
				*status == OUT_QUOTE)
			break ;
		(*i)++;
	}
}

int	sub_part_split(char *str, t_tabint *tab, char **new_tab)
{
	while (str[(*tab).i] && is_space(str[(*tab).i]) == SUCCESS)
		((*tab).i)++;
	if (str[(*tab).i] && is_space(str[(*tab).i]) == FAIL)
	{
		(*tab).start = (*tab).i;
		sub_split(str, &((*tab).i), &((*tab).status));
		if ((*tab).i != (*tab).start)
		{
			new_tab[((*tab).index)++] = \
			ft_strdup_split(str, (*tab).start, (*tab).i);
			if (!new_tab[(*tab).index - 1])
				return (free_all(new_tab), FAIL);
		}
		if (str[(*tab).i] && is_separators(str[(*tab).i]) == SUCCESS)
		{
			(*tab).start = (*tab).i;
			while (str[(*tab).i] && is_separators(str[(*tab).i]) == SUCCESS)
				((*tab).i)++;
			new_tab[((*tab).index)++] = \
			ft_strdup_split(str, (*tab).start, (*tab).i);
			if (!new_tab[(*tab).index - 1])
				return (free_all(new_tab), FAIL);
		}
	}
	return (SUCCESS);
}

char	**ft_split(char *str)
{
	char		**new_tab;
	t_tabint	tab;

	init_tab(&tab);
	new_tab = malloc((compute_size(str) + 1) * sizeof(char *));
	if (!new_tab)
		return (0);
	while (str[tab.i])
	{
		if (sub_part_split(str, &tab, new_tab) == FAIL)
			return (NULL);
	}
	new_tab[tab.index] = 0;
	return (new_tab);
}
