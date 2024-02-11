#include "../header/minishell.h"

char	*empty_strdup(void)
{
	char	*dest;

	dest = malloc(sizeof(char));
	if (dest == NULL)
		return (NULL);
	dest[0] = '\0';
	return (dest);
}

void	size_strdup_quote(int *size, int start, int end, char *src)
{
	*size = end - start;
	if (is_single_quote(src, start, end) == SUCCESS || \
		is_str_quoted(src, start, end) == SUCCESS)
		*size -= 2;
}

char	*ft_strdup_quote(char *src, int start, int end)
{
	int		size_src;
	int		origin;
	char	*dest;
	int		i;

	origin = start;
	size_strdup_quote(&size_src, start, end, src);
	if (size_src + 1 < 0)
		return (NULL);
	if (ft_strcmp(src, "\0") == SUCCESS)
		return (empty_strdup());
	dest = malloc((size_src + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (start < end)
	{
		if (src[start] && (start == end - 1 || start == origin) && \
			(src[start] == '\'' || src[start] == '"'))
			start++;
		else
			dest[i++] = src[start++];
	}
	dest[i] = '\0';
	return (dest);
}
