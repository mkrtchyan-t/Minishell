#include "minishell.h"

void 	han(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\b\b  \b\b", 6);
		exit (1);
	}
}

void	heredoc(t_all *all)
{
	char	*input;
	char	c;
	int		fd[2];
	pid_t  	pid;
	int 	fdes;
	int 	status;
	t_heredoc *tmp;

	tmp = all->here;
	while (all->here)
	{
		fdes = open("/tmp/heredoc", O_WRONLY|O_CREAT|O_TRUNC, 0600);
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			close (fd[0]);
			signal(SIGQUIT, SIG_IGN);
			signal(SIGINT, han);
			while (1)
			{
				input = readline("> ");
				if (input)
				{
					if (ft_strcmp(input, all->here->heredoc) == 0)
					{
						free(input);
						input = NULL;
						close(fd[1]);
						exit(0) ;
					}
					checkdolar(&input, all);
					ft_putstr_fd(1, input, fd[1]);
				}
				else
					exit(0) ;
			}
		}
		else if (pid < 0)
		{
			ft_putstr_fd(1, strerror(errno), 2);
		}
		else
		{
			g_glob.forked = 1;
			g_glob.here = 1;
			waitpid(pid, &status, 0);
			g_glob.forked = 0;
			g_glob.here = 0;
			if (WEXITSTATUS(status) == 1)
			{
				all->return_val = 1;
				close(fdes);
				close(fd[1]);
				close(fd[0]);
				return ;
			}
			close(fd[1]);
			while (read(fd[0], &c, sizeof(char)) != 0)
			{
				write(fdes, &c, 1);
			}
			close(fd[0]);
			all->here->file = ft_strdup("/tmp/heredoc");
		}
		all->here = all->here->next;
	}
	all->here = tmp;
}