#include "minishell.h"

void	ft_setenv(char **envp, char *key, char *value)
{
	int		i;
	char	*line;
	char	*tmp;

	i = 0;
	key = ft_strjoin(key, "=");
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0)
		{
			line = ft_strjoin(key, value);
			tmp = envp[i];
			envp[i] = ft_strdup(line);
			free(tmp);
			free(line);
			break ;
		}
		i++;
	}
	if (!envp[i])
	{
		line = ft_strjoin(key, value);
		tmp = envp[i];
		envp[i] = ft_strdup(line);
		envp[++i] = NULL;
		free(tmp);
		free(line);
	}
	free(key);
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
	free(var);
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