#include "../header/minishell.h"

int	ft_strlen_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

int	ft_strlen(char *tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

int	ft_size_env_list(t_var_env *env_list)
{
	int	size;

	size = 0;
	while (env_list != NULL)
	{
		size++;
		env_list = env_list->next;
	}
	return (size);
}
