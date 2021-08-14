#include "minishell.h"

int	var_check(t_all *all, int i, int *fd)
{
	char	*tmp;

	if (all->cmd->parsed[i][0] == '$' && all->cmd->parsed[i][1] != '?')
	{
		tmp = ft_strdup(&all->cmd->parsed[i][1]);
		ft_putstr_fd(0, ft_getenv(all->envp, tmp), *fd);
	}
	return (i);
}

static int	echo_helper(t_all *all, int *fd)
{
	int		i;
	int		size;

	i = 0;
	if (!all->cmd->parsed[1])
	{
		write(*fd, "\n", 1);
		return (errno);
	}
	size = cmdline_size(all->cmd->parsed);
	if (ft_strcmp(all->cmd->parsed[1], "-n") == 0)
		i++;
	while(++i < size)
	{
		i = var_check(all, i, fd);
		if (all->cmd->parsed[i + 1])
			write(*fd, " ", 1);
		if (i < size && ft_strcmp(all->cmd->parsed[i], "$?") == 0)
			ft_putnbr_fd(all->return_val, *fd);
		else if (i < size && all->cmd->parsed[i][0] != '$')
			write(*fd, all->cmd->parsed[i], ft_strlen(all->cmd->parsed[i]));
	}
	return (errno);
}

int	echo(t_all *all)
{
	int		fd;
	int		ret;
	t_all	*tmp;

	fd = 1;
	tmp = all;
	ret = errno;
	if (!all->redir)
	{
		ret = echo_helper(all, &fd);
	}
	else if (all->redir->fileout)
	{
		fd = (all->redir->typefileout == 1) ?
				(open(all->redir->fileout, O_WRONLY | O_TRUNC | O_CREAT, 0644)) :
				(open(all->redir->fileout, O_WRONLY | O_APPEND | O_CREAT, 0644));
		if (fd == -1)
			perror(all->redir->fileout);
		ret = echo_helper(all, &fd);
	}
	if (ft_strcmp(all->cmd->parsed[1], "-n") != 0)
		write(fd, "\n", 1);
	return (ret);
}
