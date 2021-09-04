#include "minishell.h"

void	ft_error(char *str, t_all *all)
{
	ft_putstr_fd(0, strerror(errno), 2);
	ft_putstr_fd(0, " : ", 2);
	ft_putstr_fd(1, str, 2);
	all->return_val = errno;
}

void	ft_simplerror(char *str, t_all *all)
{
	ft_putstr_fd(0, "sh: ", 2);
	ft_putstr_fd(0, str, 2);
	ft_putstr_fd(1, ": No such file or directory", 2);
	all->return_val = 127;
}