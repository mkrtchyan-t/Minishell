#include "minishell.h"

char	*get_cmd(t_all *all)
{
	int		i;
	char	**command;

	command = ft_split(all->cmd->parsed[0], '/');
	i = 0;
	while (command[i + 1])
		i++;
	return (command[i]);
}

int	execution(t_all *all)
{
	char	**path;
	int		i;
	int		res;
	int		len;
	DIR		*dir;
	int		pid;
	struct	dirent *dp;
	char	*newname;

	i = 0;
	res = 0;

	if(all->cmd->parsed[0][0] == '/')
	{
		newname = all->cmd->parsed[0];
		all->cmd->parsed[0] = get_cmd(all);
		pid = fork();
		if (pid == 0)
		{
			if ((execve(newname, all->cmd->parsed, NULL)) != 0) //executes the command
			{
				perror(newname);
			}
		}
		else if (pid < 0)
		{
			perror("error");
		}
		wait(0);
		return (errno);
	}
	path = ft_split(ft_getenv(all->envp, "PATH"), ':');
	if (!path)
	{
		ft_putstr_fd(0, "sh: ", 1);
		ft_putstr_fd(0, all->cmd->parsed[0], 1);
		ft_putstr_fd(1, ": No such file or directory", 1);
		all->return_val = 127;
		return (0);
	}
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
				pid = fork();
				if (pid == 0)
				{
					if ((execve(ft_strjoin(path[i], newname), all->cmd->parsed, NULL)) == -1) //executes the command
					{
						printf("errno: %d\n", errno);
						perror(all->cmd->parsed[0]);
					}
				}
				else if (pid < 0)
					perror("error");
				else
				{
					wait(0);
					res = 1;
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
		all->return_val = 127;
	}
	free(path);
	closedir(dir);
	// all->return_val = errno;
	return (1);
}

void	control_center(t_all *all)
{
	if (all->cmd->parsed && !all->redir)
	{
		if (!builtin(all))
			execution(all);
	}
	else if (all->cmd->parsedpipe || all->redir)
		pipe_commands(all, all->cmd, 1);
	return ;
}