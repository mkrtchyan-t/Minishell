#include "minishell.h"

static int	echo_helper(t_all *all, char **arg)
{
	int		i;
	int		size;

	i = 1;
	if (!arg[1])
	{
		write(1, "\n", 1);
		return (errno);
	}
	size = cmdline_size(arg);
	while (ft_strcmp(arg[i], "-n") == 0)
		i++;
	while(i < size)
	{
		write(1, arg[i], ft_strlen(arg[i]));
		write(1, " ", 1);
		i++;
	}
	return (errno);
}

int	echo(t_all *all, char **arg)
{
	int		fd;
	int		ret;
	t_all	*tmp;

	tmp = all;
	ret = errno;
	ret = echo_helper(all, arg);
	if (arg[1])
		if (ft_strcmp(arg[1], "-n") != 0)
			write(fd, "\n", 1);
	return (ret);
}
