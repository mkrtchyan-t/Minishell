#include "minishell.h"

static char	**delete_arg(char **envp, int i)
{
	int		j;
	char	**env;

	j = -1;
	env = (char **)malloc(sizeof(char *) * (env_size(envp)));
	while (++j < i)
	{
		env[j] = ft_strdup(envp[j]);
	}
	while(envp[++i])
	{
		env[j] = ft_strdup(envp[i]);
		j++;
	}
	return (env);
}

void	print_env2(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (has_value(env[i]))
			ft_putstr_fd(1, env[i], 1);
		i++;
	}
}

char	**unset(t_all *all, char **arg)
{
	int		i;
	int		j;
	int		size;
	char	**env;
	char	**tmp;

	j = 0;
	env = all->envp;
	while (arg[++j])
	{
		i = 0;
		while (env[i])
		{
			size = ft_strlen(arg[j]);
			if (ft_strncmp(env[i], arg[j], size) == 0 &&
				(env[i][size] == '=' || !env[i][size + 1]))
			{
				tmp = env;
				env = delete_arg(env, i);
				freestrpiped(tmp);
				break ;
			}
			i++;
		}
	}
	return (env);
}