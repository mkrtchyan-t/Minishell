#include "minishell.h"

int	cd(t_all *all)
{
	char	*path;
	char	*tmp;
	char	pwd[1024];

	ft_setenv(all->envp, "OLDPWD", getcwd(pwd, sizeof(pwd)));
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
			path = ft_strjoin(path, tmp);
		}
		else
			path = all->cmd->parsed[1];
		if (chdir(path) != 0)
			perror(path);
		strerror(errno);
	}
	ft_setenv(all->envp, "PWD", getcwd(pwd, sizeof(pwd)));
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
	int	i;

	i = 0;
	while (all->envp[i])
	{
		if (has_value(all->envp[i]))
			ft_putstr_fd(1, all->envp[i], 1);
		i++;
	}
}