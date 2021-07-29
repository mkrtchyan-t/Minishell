#include "minishell.h"

char	**export_(t_all *all)
{
	int		i;
	int		size;
	char	**env;

	i = -1;
	size = env_size(all->envp);
	env = (char **)malloc(sizeof(char *) * (env_size(all->envp) + 1));
	while (++i < size)
	{
		env[i] = ft_strdup(all->envp[i]);
	}
	if (all->cmd->parsed[1])
		env[size] = ft_strdup(all->cmd->parsed[1]);
	else
	{
		i = 0;
		while (all->envp[i])
		{
			ft_putstr_fd(0, "declare -x ", 1);
			ft_putstr_fd(1, all->envp[i++], 1);
		}
	}
	return (env);
}