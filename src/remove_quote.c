#include "../header/minishell.h"

static void	init_quote(t_quote *quote)
{
	(*quote).status = OUT_QUOTE;
	(*quote).value = '"';
	(*quote).size = 0;
}

static void	mini_update(t_quote *quote, int *i)
{
	(*quote).status = change_status_or_not((*quote).status);
	(*i)++;
}

int	size_without_quote(char *cmd)
{
	int		i;
	t_quote	quote;

	i = 0;
	init_quote(&quote);
	if (cmd && (cmd[i] == '"' || cmd[i] == '\''))
		modif_param(&quote.value, cmd[i++], &quote.status);
	while (cmd && cmd[i])
	{
		if (cmd[i] == quote.value && quote.status == IN_QUOTE)
		{
			quote.status = change_status_or_not(quote.status);
			i++;
		}
		else if ((cmd[i] == '"' || cmd[i] == '\'') && quote.status == OUT_QUOTE)
			modif_param(&quote.value, cmd[i++], &quote.status);
		else
		{
			quote.size++;
			i++;
		}
	}
	return (quote.size);
}

char	*remove_quote(char *cmd)
{
	char	*result;
	int		i;
	int		j;
	t_quote	quote;

	i = 0;
	j = 0;
	init_quote(&quote);
	quote.size = size_without_quote(cmd) + 1;
	result = malloc(quote.size * sizeof(char));
	if (!result)
		return (free(cmd), NULL);
	if (cmd && (cmd[i] == '"' || cmd[i] == '\''))
		modif_param(&quote.value, cmd[i++], &quote.status);
	while (cmd && cmd[i])
	{
		if (cmd[i] == quote.value && quote.status == IN_QUOTE)
			mini_update(&quote, &i);
		else if ((cmd[i] == '"' || cmd[i] == '\'') && quote.status == OUT_QUOTE)
			modif_param(&quote.value, cmd[i++], &quote.status);
		else
			result[j++] = cmd[i++];
	}
	result[j] = '\0';
	return (free(cmd), cmd = NULL, result);
}
