#include "minishell.h"

static int	isnum(char *s)
{
	int	i;
	int	l;

	l = 1;
	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i++]))
		{
			l = 0;
			break ;
		}
	}
	if (i == 0)
		return (0);
	return (l);
}

void	exit_(t_all *all, char **arg)
{
	int	i;
	int	l;

	l = 1;
	i = 0;
	if (!arg[1])
	{
		goodbye_msg();
		exit (0);
	}
	if (!((arg[1][0] == '-' && isnum(&arg[1][1])) || (isnum(&arg[1][0]))))
	{
		ft_putstr_fd(0, "sh: exit: ", 1);
		ft_putstr_fd(0, arg[1], 1);
		ft_putstr_fd(1, ": numeric argument required", 2);
		exit(255);
	}
	else if (arg[2])
	{
		ft_putstr_fd(1, "sh: exit: too many arguments", 2);
		all->return_val = 1;
	}
	else if (isnum(arg[1]))
		exit(ft_atoi(arg[1]));
	else if (arg[1][0] == '-' && isnum(&arg[1][1]))
		exit (256 - ft_atoi(&arg[1][1]) % 256);
}

int	builtin(t_all *all, char **arg)
{
	int i;

	i = 0;
	while (arg[i])
	{
		if (ft_strcmp(arg[i], "pwd") == 0)
		{
			all->return_val = pwd();
			return (1);
		}
		else if (ft_strcmp(arg[i], "cd") == 0)
		{
			cd(all, arg);
			return (1);
		}
		else if (ft_strcmp(arg[i], "exit") == 0)
		{
			exit_(all, arg);
			return (1);
		}
		else if (ft_strcmp(arg[i], "echo") == 0)
		{
			echo(all, arg);
			return (1);
		}
		else if (ft_strcmp(arg[i], "export") == 0)
		{
			all->envp = export_(all, arg);
			return (1);
		}
		else if (ft_strcmp(arg[i], "unset") == 0)
		{
			all->envp = unset(all, arg);
			return (1);
		}
		else if (ft_strcmp(arg[i], "env") == 0)
		{
			print_env(all);
			return (1);
		}
		i++;
	}
	return (0);
}