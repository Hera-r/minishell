#include "../header/minishell.h"

void	modif_param(char *c, char value, int *status)
{
	*c = value;
	*status = change_status_or_not(*status);
}

void	ft_putstr_fd(char *str, int fd)
{
	int		i;
	int		status;
	char	c;

	i = 0;
	status = OUT_QUOTE;
	c = '"';
	if (str && (str[i] == '"' || str[i] == '\''))
		modif_param(&c, str[i++], &status);
	while (str && str[i])
	{
		if (str[i] == c && status == IN_QUOTE)
		{
			status = change_status_or_not(status);
			i++;
		}
		else if ((str[i] == '"' || str[i] == '\'') && status == OUT_QUOTE)
			modif_param(&c, str[i++], &status);
		else
			write(fd, &str[i++], 1);
	}
}

void	ft_putstr_nl_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str && str[i] != '\0')
	{
		write(fd, &str[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}
