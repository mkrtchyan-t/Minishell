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

void	export_env(char **envp)
{
	int		i;
	char	**splitted;

	i = 0;
	while (envp[i])
	{
		splitted = ft_split(envp[i], '=');
		ft_putstr_fd(0, "declare -x ", 1);
		ft_putstr_fd(0, splitted[0], 1);
		if (splitted[1])
		{
			ft_putstr_fd(0, "=\"", 1);
			ft_putstr_fd(0, splitted[1], 1);
			ft_putstr_fd(0, "\"", 1);
		}
		write(1, "\n", 1);
		i++;
	}
}

static 	int space(t_all *all, char **arg)
{
	int		i;
	int		done;
	int		var_size;
	int		size;

	done = 0;
	size = env_size(all->envp);
	var_size = ft_strclen(arg[1], '=') + 1;
	i = -1;
	while (++i < size)
	{
		if (ft_strncmp(all->envp[i], arg[1], var_size) != 0)
			;
		else
			done = 1;
	}
	if (!done)
	{
		size++;
	}
	return (size);
}

char	**export_(t_all *all, char **arg)
{
	int		i;
	int		done;
	int		var_size;
	int		size;
	char	**env;

	if (!arg[1])
	{
		export_env(all->envp);
		return (all->envp);
	}
	done = 0;
	size = env_size(all->envp);
	var_size = ft_strclen(arg[1], '=') + 1;
	i = 0;
	env = (char **)malloc(sizeof(char *) * (space(all, arg) + 1));
	while (i < size)
	{
		if (ft_strncmp(all->envp[i], arg[1], var_size) != 0)
			env[i] = ft_strdup(all->envp[i]);
		else
		{
			env[i] = ft_strdup(arg[1]);
			done = 1;
		}
		i++;
	}
	if (!done)
	{
		env[i] = ft_strdup(arg[1]);
		env[i + 1] = NULL;
	}
	else
		env[i] = NULL;
	return (env);
}
