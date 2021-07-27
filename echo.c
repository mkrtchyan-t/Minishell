#include "minishell.h"

void	var_check(t_all *all, int *i)
{
	char	*tmp;

	if (all->cmd->parsed[*i][0] == '$')
	{
		if (!all->cmd->parsed[*i][1])
		{
			ft_putstr_fd(getenv(all->cmd->parsed[++(*i)]), 1);
		}
		else
		{
			tmp = all->cmd->parsed[*i];
			tmp++;
			printf("tmp: %s\n", tmp);
			ft_putstr_fd(getenv(tmp), 1);
		}
	}
	i++;
	all->return_val = errno;
}

static void	echo_helper(t_all *all, int *fd)
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
		var_check(all, &i);
		printf("i: %d\n", i);
		if (ft_strcmp(all->cmd->parsed[i], "$?") == 0)
			ft_putnbr_fd(all->return_val, *fd);
		else
			write(*fd, all->cmd->parsed[i], ft_strlen(all->cmd->parsed[i]));
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
	{
		echo_helper(all, &fd);
	}
	else if (all->redir->fileout)
	{
		fd = (all->redir->typefileout == 1) ?
				(open(all->redir->fileout, O_WRONLY | O_TRUNC | O_CREAT, 0644)) :
				(open(all->redir->fileout, O_WRONLY | O_APPEND | O_CREAT, 0644));
		if (fd == -1)
			perror(all->redir->fileout);
		echo_helper(all, &fd);
	}
	all->return_val = errno;
}