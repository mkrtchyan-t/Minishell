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
		if (has_value(envp[i]))
		{
			if (splitted[1])
			{
				ft_putstr_fd(0, "=\"", 1);
				ft_putstr_fd(0, splitted[1], 1);
				ft_putstr_fd(0, "\"", 1);
			}
			else
				ft_putstr_fd(0, "=\"\"", 1);
		}
		write(1, "\n", 1);
		freestrpiped(splitted);
		i++;
	}
}

static int	space(t_all *all, char **arg)
{
	int		i;
	int		done;
	int		var_size;
	int		size;
	int		j;

	j = 1;
	i = -1;
	size = env_size(all->envp);
	while (arg[j] != NULL)
	{
		size++;
		j++;
	}
	return (size);
}

int	check_arg(char *arg)
{
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
	{
		ft_putstr_fd(0, "sh: export: \'", 2);
		ft_putstr_fd(0, arg, 2);
		ft_putstr_fd(1, "\': not a valid identifier", 2);
		return (1);
	}
	return (0);
}

char	**export_(t_all *all, char **arg)
{
	int		i;
	int		j;
	int		done;
	char	**tmp;
	int		size;
	char	**env;
	char	**envp;

	if (!arg[1])
	{
		export_env(all->envp);
		return (all->envp);
	}
	envp = all->envp;
	j = 0;
	env = (char **)malloc(sizeof(char *) * (space(all, arg) + 1));
	while (arg[++j])
	{
		size = (has_value(arg[j])) ? (ft_strclen(arg[j], '='))
				: (ft_strlen(arg[j]));
		if (check_arg(arg[j]))
		{
			all->return_val = 1;
			continue ;
		}
		i = 0;
		done = 0;
		while (i < env_size(envp))
		{
			if ((has_value(envp[i]) && ft_strncmp(envp[i], arg[j], ft_strclen(envp[i], '=')) == 0))
			{
				env[i] = (has_value(arg[j])) ? (ft_strdup(arg[j]))
						: (ft_strdup(envp[i]));
				done = 1;
			}
			else if (ft_strcmp(envp[i], arg[j]) != 0)
				env[i] = ft_strdup(envp[i]);
			else
			{
				env[i] = ft_strdup(arg[j]);
				done = 1;
			}
			i++;
		}
		if (!done)
		{
			env[i] = ft_strdup(arg[j]);
			env[i + 1] = NULL;
		}
		else
			env[i] = NULL;
		tmp = envp;
		envp = copy_env(env);
		i = 0;
		while (env[i])
			free(env[i++]);
		i = 0;
		freestrpiped(tmp);
	}
	free(env);
	return (envp);
}
