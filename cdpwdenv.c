#include "minishell.h"

char	*ft_getenv(char **envp ,char *var)
{
	int		i;
	int		size;
	char	*path;

	i = 0;
	path = NULL;
	size = env_size(envp);
	printf("env size: %d\n", size);
	var = ft_strjoin(var, "=");
	printf("var: %s\n", var);
	while (i < size)
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0)
		{
			path = ft_strdup(&envp[i][ft_strlen(var)]);
		}
		printf("i: %d\n", i);
		i++;
	}
	if (i == size && !path)
		return (NULL);
	printf("path: %s\n", path);
	return (path);
}

int	cd(t_all *all)
{
	char	*path;
	char	*tmp;

	if (all->cmd->parsed[1] == NULL)
	{
		path = ft_getenv(all->envp, "HOME");
		if (chdir(path) != 0)
			ft_putstr_fd(1, "sh: cd: HOME not set", 1);
	}
	else
	{
		if (all->cmd->parsed[1][0] == 126)
		{
			tmp = ft_substr(all->cmd->parsed[1], 1, ft_strlen(all->cmd->parsed[1]) - 1);
			path = ft_strjoin(getenv("HOME"), tmp);
		}
		else
			path = all->cmd->parsed[1];
		if (chdir(path) != 0)
			perror(path);
		strerror(errno);
	}
	printf("errno: %d\n", errno);
	return (errno);
}

int	pwd(void)
{
	char cwd[1024];

	getcwd(cwd, sizeof(cwd));
	ft_putstr_fd(1, cwd, 1);
	return (errno);
}

void	print_env(t_all *all)
{
	int 	i;

	i = 0;
	while (all->envp[i])
		ft_putstr_fd(1, all->envp[i++], 1);
}