#include "../header/minishell.h"

void	display_sort_env(t_data *data)
{
	int		i;
	char	**tab;

	tab = from_list_to_tab((*data).env_list);
	if (!tab)
		return ;
	sort_env_tab(tab);
	i = 0;
	while (tab[i])
	{
		ft_putstr_fd("declare -x ", data->output_fd);
		ft_putstr_nl_fd(tab[i], data->output_fd);
		i++;
	}
	if (tab)
		free_all(tab);
}

void	sort_env_tab(char **env_tab)
{
	int		i;
	int		sorted;
	int		size;
	char	*tmp;

	sorted = 0;
	size = ft_strlen_tab(env_tab);
	while (env_tab && sorted == 0)
	{
		sorted = 1;
		i = 0;
		while (i < size - 1)
		{
			if (ft_strcmp(env_tab[i], env_tab[i + 1]) > 0)
			{
				tmp = env_tab[i];
				env_tab[i] = env_tab[i + 1];
				env_tab[i + 1] = tmp;
				sorted = 0;
			}
			i++;
		}
		size--;
	}
}
