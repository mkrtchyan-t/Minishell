#include "minishell.h"

// echo +
// cd
// pwd +
// export
// unset
// env +
// exit +

int	cd(t_cmdfinal *cmd)
{
	if (cmd->parsed[1] == NULL)
	{
		if (chdir(getenv("HOME")) != 0)
			strerror(errno);
	}
	else if (chdir(cmd->parsed[1]) != 0)
		strerror(errno);
	return (1);
}

void	pwd(void)
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

void	echo_helper(t_all *all, int *fd)
{
	int		i;
	int		size;

	if (!all->cmd->parsed[1])
	{
		write(*fd, "\n", 1);
		return ;
	}
	size = cmdline_size(all->cmd->parsed);
	if (all->cmd->parsed[1] && (ft_strcmp(all->cmd->parsed[1], "-n")) == 0)
		i = 1;
	else
		i = 0;
	while(++i < size)
	{
		if (ft_strcmp(all->cmd->parsed[i], "$?") != 0)
			write(*fd, all->cmd->parsed[i], ft_strlen(all->cmd->parsed[i]));
		else if (i < size)
			ft_putnbr_fd(errno, *fd);
		if (all->cmd->parsed[i + 1])
			write(*fd, " ", 1);
	}
	if (ft_strcmp(all->cmd->parsed[1], "-n") != 0)
	write(*fd, "\n", 1);
}

void	echo(t_all *all)
{
	int		fd;
	t_all	*tmp;

	fd = 1;
	tmp = all;
	if (!all->redir)
		echo_helper(all, &fd);
	else
	{
		while (all->redir && all->redir->type == 2)
		{
			if((fd = open(all->redir->file, O_WRONLY | O_CREAT, 0777)) == -1 )
			{
				perror(all->redir->file);
				exit(1);
			}
			echo_helper(all, &fd);
			all->redir = all->redir->next;
		}
		all = tmp;
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
			pwd();
			return (1);
		}
		else if (ft_strcmp(all->cmd->parsed[i], "cd") == 0)
		{
			// ft_putstr_fd("i still dont work:)", 1);
			cd(all->cmd);
			return (1);
		}
		else if (ft_strcmp(all->cmd->parsed[i], "exit") == 0)
		{
			// goodbye_msg();
			exit(0);
		}
		else if (ft_strcmp(all->cmd->parsed[i], "echo") == 0)
		{
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