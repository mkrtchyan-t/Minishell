#include "minishell.h"

void	pipe_commands(t_all *all, t_cmdfinal *command, int p_count)
{
	int		i;
	int		j;
	int		status;
	int		pipefds[2 * p_count];
	pid_t	pid;

	i = 0;
	while (i < p_count)
	{
		if (pipe(pipefds + i * 2) < 0)
		{
			perror("couldn't pipe");
		}
		i++;
	}

	j = 0;
	while (command)
	{
		pid = fork();
		if (pid == 0)
		{
			// if not last
			if (command->next)
			{
				if (dup2(pipefds[j + 1], 1) < 0)
				{
					perror("dup2");
				}
			}
			// if not first
			if (j != 0)
			{
				if (dup2(pipefds[j - 2], 0) < 0)
				{
					perror("dup2");
				}
			}
			i = 0;
			while (i < p_count * 2)
				close(pipefds[i++]);
			if (/* CALLING FUNCTION FOR EXECVE HERE */ 0)
			{
				perror(command->parsedpipe);
			}
		}
		else if (pid < 0)
		{
			perror("error");
		}
		command = command->next;
		j += 2;
	}
	i = 0;
	while (i < p_count * 2)
		close(pipefds[i++]);
	i = 0;
	while (i < p_count)
		wait(&status);
}