#include "minishell.h"

int	cd(t_all *all, char **arg)
{
	char	*path;
	char	*oldpwd;
	char	*tmp;
	char	pwd[1024];

	oldpwd = getcwd(pwd, sizeof(pwd));
	if (arg[1] == NULL)
	{
		path = ft_getenv(all->envp, "HOME");
		if (chdir(path) != 0)
		{
			all->return_val = 1;
			ft_putstr_fd(1, "sh: cd: HOME not set", 2);
		}
		if (path)
			free(path);
	}
	else if (ft_strcmp(arg[1], "-") == 0)
	{
		if ((tmp = ft_getenv(all->envp, "OLDPWD")) == NULL)
		{
			all->return_val = 1;
			ft_putstr_fd(1, "sh: cd: OLDPWD not set", 2);
			return (all->return_val);
		}
		if (chdir(tmp) != 0)
		{
			all->return_val = 1;
			perror(arg[1]);
		}
		ft_putstr_fd(1, tmp, 1);
		free(tmp);
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
		{
			all->return_val = 1;
			perror(arg[1]);
		}
		if (arg[1][0] == 126)
		{
			if (path)
				free(path);
			free(tmp);
		}
	}
	ft_setenv(all->envp, "OLDPWD", oldpwd);
	ft_setenv(all->envp, "PWD", getcwd(pwd, sizeof(pwd)));
	return (1);
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