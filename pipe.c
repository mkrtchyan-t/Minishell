#include "minishell.h"

int	ft_execve(t_all *all)
{
	// printf("ft execve\n");
	char	**path;
	int		i;
	int		res;
	int		len;
	DIR		*dir;
	struct	dirent *dp;
	char	*newname;

	i = 0;
	res = 0;
	if(all->cmd->parsed[0][0] == '/')
	{
		newname = all->cmd->parsed[0];
		all->cmd->parsed[0] = get_cmd(all);
		if ((execve(newname, all->cmd->parsed, NULL)) != 0) //executes the command
		{
			perror(newname);
		}
		wait(0);
		return (errno);
	}
	path = ft_split(getenv("PATH"), ':');
	newname = ft_strjoin("/", all->cmd->parsed[0]);
	while (path[i])
	{
		if (!(dir = opendir(path[i])))
			exit (1);
		len = ft_strlen(all->cmd->parsed[0]);
		while ((dp = readdir(dir)) != NULL)
		{
			if (dp->d_namlen == len && ft_strcmp(dp->d_name, all->cmd->parsed[0]) == 0) //if the command is found
			{
				if ((execve(ft_strjoin(path[i], newname), all->cmd->parsed, NULL)) != 0) //executes the command
				{
					perror(all->cmd->parsed[0]);
					// printf("executed\n");
				}
			}
		}
		i++;
	}
	if (res == 0)
	{
		ft_putstr_fd(0, "sh: ", 1);
		ft_putstr_fd(0, all->cmd->parsed[0], 1);
		ft_putstr_fd(1, ": command not found", 1);
	}
	free(path);
	closedir(dir);
	return (1);
}

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
			if (ft_execve(all))
			{
				perror(command->parsedpipe[0]);
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
	{
		wait(&status);
		i++;
	}
}