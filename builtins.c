#include "minishell.h"

// echo
// cd
// pwd +
// export
// unset
// env +
// exit +

int	sh_cd(t_cmdfinal *cmd)
{
	if (cmd->parsed[1] == NULL)
	{
		if (chdir("~/") != 0)
			strerror(errno);
	}
	else if (chdir(cmd->parsed[1]) != 0)
		strerror(errno);
	return (1);
}

void	sh_pwd(void)
{
	char cwd[1024];

	getcwd(cwd, sizeof(cwd));
	ft_putstr_fd(cwd, 1);
}

void	print_env(t_all *all)
{
	int 	i;

	i = 0;
	if (all->cmd->parsed[1])
	{
		write(1, "env: ", 5);
		write(1, all->cmd->parsed[1], 1024);
		write(1, ": Permission denied\n", 20);
		return ;
	}
	while (all->envp[i])
		ft_putstr_fd(all->envp[i++], 1);
}

void	echo(t_all *all)
{
	int	i;
	int	size;

	if (!all->cmd->parsed[1])
	{
		write(1, "\n", 1);
		return ;
	}
	size = cmdline_size(all->cmd->parsed);
	if (all->cmd->parsed[1] && (ft_strcmp(all->cmd->parsed[1], "-n")) == 0)
		i = 1;
	else
		i = 0;
	// printf("i: %d\n", i);
	// printf("argv: %s\n", all->cmd->parsed[i]);
	while(++i < size)
	{
		write(1, all->cmd->parsed[i], ft_strlen(all->cmd->parsed[i]));
		if (all->cmd->parsed[i + 1])
			write(1, " ", 1);
	}
	if (ft_strcmp(all->cmd->parsed[1], "-n") != 0)
		write(1, "\n", 1);
}

int	builtin(t_all *all)
{
	int i;

	i = 0;
	while (all->cmd->parsed[i])
	{
		if (ft_strcmp(all->cmd->parsed[i], "pwd") == 0)
		{
			sh_pwd();
			return (1);
		}
		else if (ft_strcmp(all->cmd->parsed[i], "cd") == 0)
		{
			// ft_putstr_fd("i still dont work:)", 1);
			sh_cd(all->cmd);
			return (1);
		}
		else if (ft_strcmp(all->cmd->parsed[i], "exit") == 0)
		{
			// goodbye_msg();
			exit(0);
		}
		else if (ft_strcmp(all->cmd->parsed[i], "echo") == 0)
		{
			// ft_putstr_fd("i still dont work:)", 1);
			echo(all);
			return (1);
		}
		else if (ft_strcmp(all->cmd->parsed[i], "export") == 0)
		{
			ft_putstr_fd("i still dont work:)", 1);
			return (1);
		}
		else if (ft_strcmp(all->cmd->parsed[i], "unset") == 0)
		{
			ft_putstr_fd("i still dont work:)", 1);
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