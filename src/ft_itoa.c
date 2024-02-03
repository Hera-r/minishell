#include "../header/minishell.h"

static int	ft_cpte_size(int nb)
{
	int	size;

	size = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		size++;
		nb *= -1;
	}
	while (nb)
	{
		nb /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int nb)
{
	char	*result;
	int		size;

	size = ft_cpte_size(nb);
	result = malloc((size + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	result[size] = '\0';
	size--;
	if (nb == 0)
		return (result[0] = '0', result);
	if (nb < 0)
	{
		result[0] = '-';
		nb *= -1;
	}
	while (nb)
	{
		result[size] = (nb % 10) + '0';
		nb /= 10;
		size--;
	}
	return (result);
}
