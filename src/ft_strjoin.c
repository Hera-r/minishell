#include "../header/minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new_str;
	int		size;
	int		i;

	size = ft_strlen(s1) + ft_strlen(s2) + 2;
	new_str = malloc(size * sizeof(char));
	if (!new_str)
		return (0);
	i = 0;
	while (*s1)
		new_str[i++] = *(s1++);
	new_str[i++] = '/';
	while (*s2 && *s2 != ' ')
		new_str[i++] = *(s2++);
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_strjoin_classic(char *s1, char *s2)
{
	char	*new_str;
	int		size;
	int		i;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	new_str = malloc(size * sizeof(char));
	if (!new_str)
		return (0);
	i = 0;
	while (*s1)
		new_str[i++] = *(s1++);
	while (*s2 && *s2 != ' ')
		new_str[i++] = *(s2++);
	new_str[i] = '\0';
	return (new_str);
}
