#include "../header/minishell.h"

char	*take_value(t_var_env *env_list, char *name)
{
	while (env_list != NULL)
	{
		if (ft_strcmp(env_list->name, name) == SUCCESS)
			return (ft_strdup_quote(env_list->value, 0, \
					ft_strlen(env_list->value)));
		env_list = env_list->next;
	}
	return (NULL);
}

static void	loop_start_expand(t_node *node, char *tmp, int *i, int *elem)
{
	while (tmp && tmp[*i] && tmp[*i] != '$')
	{
		if (tmp[*i] == '"')
			(*i)++;
		else
			(*node).token[(*elem)++] = tmp[(*i)++];
	}
}

void	sub_part_expand_var(t_node *node, char *tmp, int name_size, char *value)
{
	int		i;
	int		j;
	int		elem;

	i = 0;
	j = 0;
	elem = 0;
	loop_start_expand(node, tmp, &i, &elem);
	i += name_size;
	while (value && value[j])
		(*node).token[elem++] = value[j++];
	while (tmp && tmp[i])
	{
		if (tmp[i] == '"')
			i++;
		if (tmp[i])
			(*node).token[elem++] = tmp[i++];
	}
	(*node).token[elem] = '\0';
	free(tmp);
}

int	expand_var(t_node **node_tab, int index, char *value, int name_size )
{
	int		final_size;
	char	*tmp;

	final_size = ft_strlen((*node_tab)[index].token) - name_size + \
				ft_strlen(value);
	tmp = (*node_tab)[index].token;
	(*node_tab)[index].token = malloc(final_size + 1);
	if (!(*node_tab)[index].token)
		return (free(tmp), FAIL);
	sub_part_expand_var(&((*node_tab)[index]), tmp, name_size, value);
	return (SUCCESS);
}
