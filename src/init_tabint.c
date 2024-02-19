#include "../header/minishell.h"

void	init_tab(t_tabint	*tab)
{
	(*tab).i = 0;
	(*tab).index = 0;
	(*tab).status = OUT_QUOTE;
}

void	init_size(int *size, char ***result)
{
	*size = ft_strlen_tab(*result);
	free_all(*result);
	*result = NULL;
}
