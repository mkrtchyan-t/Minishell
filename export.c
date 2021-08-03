#include "minishell.h"

int	has_value(char *env)
{
	int	i;

	i = 0;
	while(env[i] != '=' && env[i])
		i++;
	if (env[i] == '=')
		return (1);
	return (0);
}

// void	export_env(char **envp)
// {

// }

char	**export_(t_all *all)
{
	int		i;
	int		done;
	int		var_size;
	int		size;
	char	**env;

	done = 0;
	size = env_size(all->envp);
	var_size = ft_strclen(all->cmd->parsed[1], '=') + 1;
	i = -1;
	env = (char **)malloc(sizeof(char **) * (env_size(all->envp) + 1));
	while (++i < size)
	{
		if (ft_strncmp(all->envp[i], all->cmd->parsed[1], var_size) != 0)
			env[i] = ft_strdup(all->envp[i]);
		else
		{
			env[i] = ft_strdup(all->cmd->parsed[1]);
			done = 1;
		}
	}
	if (!done)
		env[size] = ft_strdup(all->cmd->parsed[1]);
	return (env);
}