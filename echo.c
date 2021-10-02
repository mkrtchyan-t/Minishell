#include "minishell.h"

int  		option(char *str)
{
	int i;

	i = 0;
	if (str[i] && str[i] == '-')
	{
		i++;
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

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
	while (arg[i] && (option(arg[i]) == 1))
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
		if (option(arg[1]) == 0)
			write(fd, "\n", 1);
}
