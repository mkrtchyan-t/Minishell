#include "minishell.h"

int	var_check(t_all *all, char **arg, int i, int *fd)
{
	char	*tmp;

	if (arg[i][0] == '$' && arg[i][1] != '?')
	{
		tmp = ft_strdup(&arg[i][1]);
		ft_putstr_fd(0, ft_getenv(all->envp, tmp), *fd);
	}
	return (i);
}

static int	echo_helper(t_all *all, char **arg, int *fd)
{
	int		i;
	int		size;

	i = 1;
	if (!arg[1])
	{
		write(*fd, "\n", 1);
		return (errno);
	}
	size = cmdline_size(arg);
	if (ft_strcmp(arg[1], "-n") == 0)
		i++;
	while(i < size)
	{
		write(*fd, arg[i], ft_strlen(arg[i]));
		write(*fd, " ", 1);
		i++;
	}
	return (errno);
}

int	echo(t_all *all, char **arg)
{
	int		fd;
	int		ret;
	t_all	*tmp;

	fd = 1;
	tmp = all;
	ret = errno;
	ret = echo_helper(all, arg, &fd);
	if (arg[1])
		if (ft_strcmp(arg[1], "-n") != 0)
			write(fd, "\n", 1);
	return (ret);
}
