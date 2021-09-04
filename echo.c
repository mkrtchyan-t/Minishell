#include "minishell.h"

static void	echo_helper(t_all *all, char **arg)
{
	int		i;
	int		size;

	i = 1;
	if (!arg[1])
	{
		write(1, "\n", 1);
		return ;
	}
	size = cmdline_size(arg);
	while (arg[i] && ft_strcmp(arg[i], "-n") == 0)
		i++;
	while(i < size)
	{
		write(1, arg[i], ft_strlen(arg[i]));
		if (i < size - 1)
			write(1, " ", 1);
		i++;
	}
}

void	echo(t_all *all, char **arg)
{
	int		fd;
	t_all	*tmp;

	tmp = all;
	echo_helper(all, arg);
	if (arg[1])
		if (ft_strcmp(arg[1], "-n") != 0)
			write(fd, "\n", 1);
}
