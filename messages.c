#include "minishell.h"

void	goodbye_msg()
{
	char	*line;
	int		fd;

	line = NULL;
	fd = open("goodbye.txt", 'r');
	while (get_next_line(fd, &line))
		ft_putstr_fd(line, 1);
}

void	welcome_msg()
{
	char	*line;
	int		fd;

	line = NULL;
	fd = open("welcome.txt", 'r');
	while (get_next_line(fd, &line))
		ft_putstr_fd(line, 1);
}