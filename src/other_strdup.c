#include "../header/minishell.h"

char	*ft_strdup_split(char *src, int start, int end)
{
	char	*dest;
	int		size_src;

	size_src = end - start;
	dest = malloc((size_src + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	return (ft_strcpy(dest, src, start, end));
}

char	*simple_strdup(char *s)
{
	char	*result;
	int		final_len;
	int		i;

	final_len = ft_strlen(s) + 1;
	result = malloc(final_len * sizeof(char));
	if (!result)
		return (0);
	i = 0;
	while (s[i])
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
