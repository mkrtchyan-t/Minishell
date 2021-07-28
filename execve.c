#include "minishell.h"

char	*set_cmd_line(t_all *all)
{
	int		i;
	char	*tmp;
	char	**command;

	tmp = all->cmd->parsed[0];
	if (tmp[0] == '/')
	{
		command = ft_split(tmp, '/');
		i = 0;
		while (command[i + 1])
			i++;
		tmp = command[i];
	}
	all->cmd->parsed[0] = tmp;
	tmp = ft_strjoin("/", tmp);
	return (tmp);
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
	newname = set_cmd_line(all);
	path = ft_split(getenv("PATH"), ':');
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
					if ((execve(ft_strjoin(path[i], newname), all->cmd->parsed, NULL)) != 0) //executes the command
						perror(all->cmd->parsed[0]);
				}
				else if (pid < 0)
					ft_putstr_fd("sh: process error", 1);
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
		write(1, "sh: ", 4);
		write(1, all->cmd->parsed[0], len);
		ft_putstr_fd(": command not found", 1);
	}
	free(path);
	closedir(dir);
	return (1);
}

// int	execution_pipe(t_all *all)
// {

// }

void	control_center(t_all *all)
{
	if (!all->cmd->parsedpipe)
		execution(all);
	// else
	//	execution_pipe(all);
}