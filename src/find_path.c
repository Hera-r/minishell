#include "../header/minishell.h"

static void	merr(char *cmd)
{
	ft_putstr_fd(cmd, STDERR);
	ft_putstr_nl_fd(": No such file or directory", STDERR);
}

static char	*merr2(char *cmd, char **tab)
{
	ft_putstr_fd(cmd, STDERR);
	ft_putstr_nl_fd(": command not found", STDERR);
	return (free_all(tab), tab = NULL, NULL);
}

static int	find_path(char *path, char *cmd)
{
	char	*result;

	result = ft_strjoin(path, cmd);
	if (!result)
		return (0);
	if (access(result, F_OK) == 0)
		return (free(result), 0);
	return (free(result), -1);
}

static char	*path_loop(char **paths, char *cmd)
{
	int		i;
	char	*result;

	i = 0;
	if (!paths)
		return (merr(cmd), NULL);
	while (paths && paths[i])
	{
		if (find_path(paths[i], cmd) == 0)
		{
			result = ft_strjoin(paths[i], cmd);
			if (!result)
				return (free(paths), paths = NULL, NULL);
			return (free_all(paths), paths = NULL, result);
		}
		i++;
	}
	return (merr2(cmd, paths));
}

char	*env_loop(char **envp, char *cmd)
{
	char	**paths;
	int		i;
	char	*start_path;

	i = 0;
	start_path = 0;
	paths = NULL;
	while (envp && envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' && \
			envp[i][2] == 'T' && envp[i][3] == 'H')
		{
			start_path = simple_strdup(envp[i] + 5);
			if (!start_path)
				return (NULL);
			paths = simple_split(start_path, ':');
			if (!paths)
				return (free(start_path), NULL);
			break ;
		}
		i++;
	}
	free(start_path);
	return (path_loop(paths, cmd));
}
