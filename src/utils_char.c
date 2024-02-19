#include "../header/minishell.h"

int	is_separators(char c)
{
	if (c == '\n' || c == '|' || c == '>' || c == '<')
		return (SUCCESS);
	return (FAIL);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\r')
		return (SUCCESS);
	return (FAIL);
}

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (SUCCESS);
	return (FAIL);
}

int	is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (SUCCESS);
	return (FAIL);
}

int	has_plus_equal(char *cmd)
{
	int	equal;

	equal = get_index_equal(cmd);
	if (equal == 0)
		return (FAIL);
	if (cmd[equal - 1] && cmd[equal - 1] == '+')
		return (SUCCESS);
	return (FAIL);
}
