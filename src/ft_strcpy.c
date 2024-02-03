#include "../header/minishell.h"

char	*ft_strcpy(char *dest, char *src, int start, int end)
{
	int	i;

	i = 0;
	while (start < end)
	{
		dest[i] = src[start];
		start++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
