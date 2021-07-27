#include "minishell.h"

int	cd(t_cmdfinal *cmd)
{
	char	*path;
	char	*tmp;

	if (cmd->parsed[1] == NULL)
	{
		if (chdir(getenv("HOME")) != 0)
			ft_putstr_fd("sh: cd: HOME not set", 1);
	}
	else
	{
		if (cmd->parsed[1][0] == 126)
		{
			tmp = ft_substr(cmd->parsed[1], 1, ft_strlen(cmd->parsed[1]) - 1);
			path = ft_strjoin(getenv("HOME"), tmp);
		}
		else
			path = cmd->parsed[1];
		if (chdir(path) != 0)
			perror(path);
		strerror(errno);
	}
	return (1);
}

void	pwd(void)
{
	char cwd[1024];

	getcwd(cwd, sizeof(cwd));
	ft_putstr_fd(cwd, 1);
}

void	print_env(t_all *all)
{
	int 	i;

	i = 0;
	if (all->cmd->parsed[1])
	{
		write(1, "env: ", 5);
		write(1, all->cmd->parsed[1], 1024);
		write(1, ": Permission denied\n", 20);
		return ;
	}
	while (all->envp[i])
		ft_putstr_fd(all->envp[i++], 1);
}