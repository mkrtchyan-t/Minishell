#include "minishell.h"

void	exit_(t_all *all, char **arg)
{
	if (!arg[1])
		exit (0);
	if (arg[2])
	{
		ft_putstr_fd(1, "sh: exit: too many arguments", 1);
		all->return_val = 1;
	}
	else if (ft_isdigit(arg[1][0]))
		exit (ft_atoi(arg[1]));
	else
	{
		ft_putstr_fd(0, "sh: exit: ", 1);
		ft_putstr_fd(0, arg[1], 1);
		ft_putstr_fd(1, ": numeric argument required", 1);
		all->return_val = 255;
	}
}

void	heredoc(t_all *all, char *arg)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (input)
			if (ft_strcmp(input, arg) == 0)
			{
				free(input);
				input = NULL;
				return ;
			}
	}
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
			all->return_val = cd(all, arg);
			return (1);
		}
		else if (ft_strcmp(arg[i], "exit") == 0)
		{
			// goodbye_msg();
			exit_(all, arg);
			return (1);
		}
		else if (ft_strcmp(arg[i], "echo") == 0)
		{
			all->return_val = echo(all, arg);
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