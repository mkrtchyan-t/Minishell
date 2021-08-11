#include "minishell.h"

void	ft_setenv(char **envp, char *value, char *key)
{
	int	i;

	i = 0;
	value = ft_strjoin(value, "=");
	while (envp[i])
	{
		if (ft_strncmp(envp[i], value, ft_strlen(value)) == 0)
			envp[i] = ft_strdup(ft_strjoin(value, key));
		i++;
	}
}

char	*ft_getenv(char **envp ,char *var)
{
	int		i;
	int		size;
	char	*path;

	i = 0;
	path = NULL;
	size = env_size(envp);
	var = ft_strjoin(var, "=");
	while (i < size)
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0)
		{
			path = ft_strdup(&envp[i][ft_strlen(var)]);
		}
		i++;
	}
	if (i == size && !path)
		return (NULL);
	return (path);
}

size_t	ft_strclen(char *str, int c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int	all_space(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}