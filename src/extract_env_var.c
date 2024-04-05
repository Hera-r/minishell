#include "../header/minishell.h"

char	*extract_name(char *cmd)
{
	int		size;
	int		i;
	char	*name;

	size = get_index_equal(cmd);
	i = 0;
	if (cmd[size - 1] == '+')
		size--;
	name = malloc((size + 1) * sizeof(char));
	if (!name)
		return (NULL);
	while (i < size)
	{
		name[i] = cmd[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*extract_value(char *cmd, char *name)
{
	int		size;
	int		i;
	int		j;
	char	*value;

	i = get_index_equal(cmd);
	j = 0;
	size = ft_strlen(cmd) - ft_strlen(name);
	if (is_double_quote(cmd, i) == SUCCESS)
		size -= 2;
	value = malloc(size * sizeof(char));
	if (!value)
		return (NULL);
	i++;
	while (cmd && cmd[i])
	{
		if (cmd[i] != '"')
		{
			value[j] = cmd[i];
			j++;
		}
		i++;
	}
	value[j] = '\0';
	return (value);
}
