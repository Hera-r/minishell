#include "../header/minishell.h"

static void	init_quote(t_quote *quote, int start, int end, t_range *r)
{
	(*quote).status = OUT_QUOTE;
	(*quote).size = end - start;
	(*quote).value = '"';
	(*r).start = start;
	(*r).end = end;
	(*r).i = 0;
}

void	sub_loop(t_range *range, t_quote *quote, char *src, char *dest)
{
	if (src[(*range).start + 1] == (*quote).value)
		(*range).start += 2;
	else
	{
		(*quote).status = change_status_or_not((*quote).status);
		dest[(*range).i++] = src[(*range).start++];
	}
}

char	*strdup_loop(t_range range, char *dest, char *src, t_quote quote)
{
	while (range.start < range.end)
	{
		if (src[range.start] == quote.value && quote.status == IN_QUOTE)
		{
			quote.status = change_status_or_not(quote.status);
			if (range.start + 1 < range.end && src[range.start + 1] == ' ')
				break ;
			dest[range.i++] = src[range.start++];
		}
		else if ((src[range.start] == '\'' || src[range.start] == '"') && \
				quote.status == OUT_QUOTE)
		{
			quote.value = src[range.start];
			sub_loop(&range, &quote, src, dest);
		}
		else
			dest[range.i++] = src[range.start++];
	}
	dest[range.i] = '\0';
	return (dest);
}

char	*ft_strdup(char *src, int start, int end)
{
	char	*dest;
	t_quote	quote;
	t_range	range;

	init_quote(&quote, start, end, &range);
	if (is_str_quoted(src, start, end) == SUCCESS)
		return (ft_strdup_quote(src, start, end));
	dest = malloc((quote.size + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	if (src[range.start] == '"' || src[range.start] == '\'')
	{
		quote.value = src[range.start];
		if (src[range.start + 1] == quote.value)
			range.start += 2;
		else
		{
			quote.status = change_status_or_not(quote.status);
			dest[range.i++] = src[range.start++];
		}
	}
	return (strdup_loop(range, dest, src, quote));
}
