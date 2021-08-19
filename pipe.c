#include "minishell.h"

int	ft_execve(t_all *all, t_cmdfinal *command, int fdout, int tmpout)
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
	if(command->parsedpipe[0][0] == '/')
	{
		newname = command->parsedpipe[0];
		command->parsedpipe[0] = get_cmd(all);
		if ((execve(newname, command->parsedpipe, NULL)) != 0) //executes the command
		{
			perror(newname);
		}
		wait(0);
		return (errno);
	}
	path = ft_split(getenv("PATH"), ':');
	newname = ft_strjoin("/", command->parsedpipe[0]);
	while (path[i])
	{
		if (!(dir = opendir(path[i])))
			exit (1);
		len = ft_strlen(command->parsedpipe[0]);
		while ((dp = readdir(dir)) != NULL)
		{
			if (dp->d_namlen == len && ft_strcmp(dp->d_name, command->parsedpipe[0]) == 0) //if the command is found
			{
				if ((execve(ft_strjoin(path[i], newname), command->parsedpipe, NULL)) != 0) //executes the command
				{
						perror(command->parsedpipe[0]);
				}
			}
		}
		i++;
	}
	if (res == 0)
	{
		ft_putstr_fd(0, "sh: ", tmpout);
		ft_putstr_fd(0, all->cmd->parsed[0], tmpout);
		ft_putstr_fd(1, ": command not found", tmpout);
	}
	free(path);
	closedir(dir);
	return (1);
}

void	pipe_commands(t_all *all, t_cmdfinal *command, int p_count)
{
	int		tmpin;
	int 	pipefd[2];
	int		tmpout;
	int  	fdout;
	int  	fdin;
	pid_t	pid;

	tmpin = dup(0);
	tmpout = dup(1);
	if (all->redir && all->redir->filein)
	{
		if (all->redir->typefilein == 1)
		{
			fdin = open(all->redir->filein, O_RDONLY);
			if (command->parsedpipe == NULL)
				command->parsedpipe = command->parsed;
		}
	}
	else
		fdin = dup(tmpin);
	while (command)
	{
		dup2(fdin, 0);
		close(fdin);
		if (command->next == NULL)
		{
			if (all->redir && all->redir->fileout)
			{
				if (all->redir->typefileout == 1)
					fdout = open(all->redir->fileout, O_WRONLY | O_CREAT | O_RDONLY | O_TRUNC, 0644);
				else
					fdout = open(all->redir->fileout, O_WRONLY | O_CREAT | O_RDONLY | O_APPEND, 0644);
				if (command->parsedpipe == NULL)
					command->parsedpipe = command->parsed;
			}
			else
				fdout = dup(tmpout);
		}
		else
		{
			pipe(pipefd);
			fdout = pipefd[1];
			fdin = pipefd[0];
		}
		dup2(fdout, 1);
		close(fdout);
		pid = fork();
		if (pid == 0)
		{
			if (!(builtin(all, command->parsedpipe)))
				ft_execve(all, command, fdout, tmpout);
		}
		command = command->next;
	}
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	waitpid(pid, NULL, 0);
}
