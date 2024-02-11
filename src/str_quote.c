#include "../header/minishell.h"

int	is_double_quote(char *str, int start)
{
	int	i;
	int	quote;

	i = start;
	quote = 0;
	while (str && str[i])
	{
		if (str[i] == '"')
			quote++;
		i++;
	}
	if (quote > 0)
		return (SUCCESS);
	return (FAIL);
}

int	is_single_quote(char *str, int start, int end)
{
	if (str[start] == '\'' && str[end - 1] == '\'')
		return (SUCCESS);
	return (FAIL);
}

int	is_str_quoted(char *str, int start, int end)
{
	int	i;

	i = start;
	if (str[i] && ((str[i] != '"' || str[end - 1] != '"') && \
		is_single_quote(str, start, end) == FAIL))
		return (FAIL);
	i++;
	while (i < (end - 1))
	{
		if (str[i] == ' ' || str[i] == '\'' || str[i] == '"')
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}
