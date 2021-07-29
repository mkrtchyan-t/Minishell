#include "minishell.h"

int	env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

static char	**delete_arg(t_all *all, int i)
{
	int		j;
	char	**env;

	j = -1;

	env = (char **)malloc(sizeof(char *) * (env_size(all->envp)));
	while (++j < i)
	{
		env[j] = ft_strdup(all->envp[j]);
	}
	while(all->envp[++i])
	{
		env[j] = ft_strdup(all->envp[i]);
		j++;
	}
	return (env);
}

char	**unset(t_all *all)
{
	int		i;
	char	**env;
	char	*str;

	i = 0;
	env = NULL;
	while (all->envp[i])
	{
		str = ft_strjoin(all->cmd->parsed[1], "=");
		if (ft_strncmp(all->envp[i], str, ft_strlen(str)) == 0)
		{
			env = delete_arg(all, i);
			break ;
		}
		i++;
	}
	return (env);
}