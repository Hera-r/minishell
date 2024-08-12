#include "../header/minishell.h"

int	ft_pwd(char **cmd)
{
	char	*buffer;

	if (cmd[1] && cmd[1][0] == '-' && cmd[1][1] && cmd[1][1] != '-')
		return (is_valid_option(cmd[0], cmd[1]), MISUSE);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (FAIL);
	if (getcwd(buffer, BUFFER_SIZE) == NULL)
	{
		perror("Error");
		return (FAIL);
	}
	ft_putstr_nl_fd(buffer, STDOUT);
	free(buffer);
	return (SUCCESS);
}
