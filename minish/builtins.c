#include "minishell.h"

// echo +
// cd +
// pwd +
// export +-
// unset +
// env +
// exit +

void	exit_(t_all *all)
{
	if (!all->cmd->parsed[1])
		exit (0);
	if (all->cmd->parsed[2])
		ft_putstr_fd(1, "sh: exit: too many arguments", 1);
	else if (ft_isdigit(all->cmd->parsed[1][0]))
		exit (atoi(all->cmd->parsed[1]));
	else
	{
		ft_putstr_fd(0, "sh: exit: ", 1);
		ft_putstr_fd(0, all->cmd->parsed[1], 1);
		ft_putstr_fd(1, ": numeric argument required", 1);
	}
}

int	builtin(t_all *all)
{
	int i;

	i = 0;
	while (all->cmd->parsed[i])
	{
		if (ft_strcmp(all->cmd->parsed[i], "pwd") == 0)
		{
			all->return_val = pwd();
			return (1);
		}
		else if (ft_strcmp(all->cmd->parsed[i], "cd") == 0)
		{
			all->return_val = cd(all);
			return (1);
		}
		else if (ft_strcmp(all->cmd->parsed[i], "exit") == 0)
		{
			// goodbye_msg();
			exit_(all);
			return (1);
		}
		else if (ft_strcmp(all->cmd->parsed[i], "echo") == 0)
		{
			all->return_val = echo(all);
			return (1);
		}
		else if (ft_strcmp(all->cmd->parsed[i], "export") == 0)
		{
			// ft_putstr_fd(1, "i still dont work:)", 1);
			all->envp = export_(all);
			return (1);
		}
		else if (ft_strcmp(all->cmd->parsed[i], "unset") == 0)
		{
			all->envp = unset(all);
			return (1);
		}
		else if (ft_strcmp(all->cmd->parsed[i], "env") == 0)
		{
			print_env(all);
			return (1);
		}
		i++;
	}
	return (0);
}