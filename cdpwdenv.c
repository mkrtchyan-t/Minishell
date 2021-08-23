#include "minishell.h"

int	cd(t_all *all, char **arg)
{
	char	*path;
	char	*tmp;
	char	pwd[1024];
	char  	*dir[2];

	dir[0] = getcwd(pwd, sizeof(pwd));
	ft_setenv(all->envp, "OLDPWD", dir[0]);
	if (arg[1] == NULL)
	{
		path = ft_getenv(all->envp, "HOME");
		if (chdir(path) != 0)
			ft_putstr_fd(1, "sh: cd: HOME not set", 1);
		if (path)
			free(path);
	}
	else
	{
		if (arg[1][0] == 126)
		{
			tmp = ft_substr(arg[1], 1, ft_strlen(arg[1]) - 1);
			path = ft_strjoin(path, tmp);
		}
		else
			path = arg[1];
		if (chdir(path) != 0)
			perror(path);
		if (arg[1][0] == 126)
		{
			if (path)
				free(path);
			free(tmp);
		}
	}
	dir[1] = getcwd(pwd, sizeof(pwd));
	ft_setenv(all->envp, "PWD", dir[1]);
	/*if (dir[0])
		free(dir[0]);
	if (dir[1])
		free(dir[1]);*/
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
	int	i;

	i = 0;
	while (all->envp[i])
	{
		if (has_value(all->envp[i]))
			ft_putstr_fd(1, all->envp[i], 1);
		i++;
	}
}