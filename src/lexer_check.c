#include "../header/minishell.h"

t_node	check_pipe(char *cmd)
{
	int		size;

	size = ft_strlen(cmd);
	if (size > 1)
		return ((t_node){T_ERROR, ft_strdup(cmd, 0, size)});
	return ((t_node){T_PIPE, ft_strdup(cmd, 0, size)});
}

t_node	check_redir(char *cmd)
{
	int		size;

	size = ft_strlen(cmd);
	if (size > 2)
		return ((t_node){T_ERROR, ft_strdup(cmd, 0, size)});
	if (size == 2)
	{
		if (cmd[0] == '>')
			return ((t_node){T_REDIR_OUT_APPEND, ft_strdup(cmd, 0, size)});
		return ((t_node){T_HEREDOC, ft_strdup(cmd, 0, size)});
	}
	else if (cmd[0] == '>')
		return ((t_node){T_REDIR_OUT, ft_strdup(cmd, 0, size)});
	else
		return ((t_node){T_REDIR_IN, ft_strdup(cmd, 0, size)});
}

int	check_unclosed_double(char *cmd)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (cmd[i] == '"')
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (SUCCESS);
	return (FAIL);
}

int	check_unclosed_single(char *cmd)
{
	int		i;
	int		count;
	int		quote;

	i = 0;
	count = 0;
	quote = OUT_QUOTE;
	while (cmd[i])
	{
		if (cmd[i] == '"')
			quote = change_status_or_not(quote);
		else if (cmd[i] == '\'' && quote == OUT_QUOTE)
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (SUCCESS);
	return (FAIL);
}

t_node	check_str(char *cmd)
{
	int		size;

	size = ft_strlen(cmd);
	if (check_unclosed_single(cmd) == FAIL || \
		check_unclosed_double(cmd) == FAIL)
		return ((t_node){T_ERROR, ft_strdup(cmd, 0, size)});
	return ((t_node){T_STR, ft_strdup_split(cmd, 0, size)});
}
