#include "../header/minishell.h"

static int	ft_compute_size(char *s, char c)
{
	int	size;

	size = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s && *s != c)
		{
			size++;
			while (*s && *s != c)
				s++;
		}
	}
	return (size);
}

char	**simple_split(char *s, char c)
{
	char	**result;
	int		start;
	int		i;
	int		index;

	result = malloc((ft_compute_size(s, c) + 1) * sizeof(char *));
	if (!result)
		return (0);
	i = 0;
	index = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			result[index] = ft_strdup(s, start, i);
			index++;
		}
	}
	result[index] = 0;
	return (result);
}
