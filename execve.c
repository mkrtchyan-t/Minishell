#include "minishell.h"

char	*get_cmd(t_all *all)
{
	int		i;
	char	**command;
	char 	*var;

	command = ft_split(all->cmd->parsed[0], '/');
	i = 0;
	while (command[i + 1])
		i++;
	var = ft_strdup(command[i]);
	freestrpiped(command);
	return (var);
}

int execdrop(t_all *all)
{
	int		pid;
	char	*newname;
	int 	status;

	newname = all->cmd->parsed[0];
	all->cmd->parsed[0] = get_cmd(all);
	pid = fork();
	if (pid == 0)
	{
		if ((execve(newname, all->cmd->parsed, NULL)) != 0) //executes the command
		{
			ft_error(newname, all);
			exit(127);
		}
	}
	else if (pid < 0)
		ft_error("error", all);
	g_glob.forked = 1;
	waitpid(pid, &status, 0);
	all->return_val = WEXITSTATUS(status);
	free(newname);
	g_glob.forked = 0;
	return (1);
}

int	execution(t_all *all)
{
	char	**path;
	int		i;
	int		res[2];
	int		len;
	DIR		*dir;
	int		pid;
	struct	dirent *dp;
	char	*newname[2];

	i = 0;
	res[0] = 0;
	if(all->cmd->parsed[0][0] == '/')
	{
		execdrop(all);
		return (1);
	}
	newname[0] = ft_getenv(all->envp, "PATH");
	path = ft_split(newname[0], ':');
	if (!path)
	{
		ft_simplerror(all->cmd->parsed[0], all);
		return (0);
	}
	newname[1] = ft_strjoin("/", all->cmd->parsed[0]);
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
					if ((execve(ft_strjoin(path[i], newname[1]), all->cmd->parsed, NULL)) == -1) //executes the command
					{
						ft_error(all->cmd->parsed[0], all);
						exit(errno);
					}
				}
				else if (pid < 0)
				{
					ft_error(all->cmd->parsed[0], all);
				}
				else
				{
					g_glob.forked = 1;
					waitpid(pid, &res[1], 0);
					all->return_val = WEXITSTATUS(res[1]);
					free(newname[1]);
					g_glob.forked = 0;
					res[0] = 1;
				}
			}
		}
		if (dir)
			closedir(dir);
		i++;
	}
	if (res[0] == 0)
	{
		if (newname[1])
			free(newname[1]);
		ft_putstr_fd(0, "sh: ", 2);
		ft_putstr_fd(0, all->cmd->parsed[0], 2);
		ft_putstr_fd(1, ": command not found", 2);
		all->return_val = 127;
	}
	freestrpiped(path);
	free(newname[0]);
	return (1);
}

void	control_center(t_all *all)
{
	if (all->redir && all->redir->filein && all->redir->typefilein == 2)
	{
		heredoc(all, all->redir->filein);
	}
	if ((all->cmd->parsed && !all->redir) || (all->cmd->parsed && \
		all->redir && all->redir->filein && \
		all->redir->typefilein == 2 && !all->redir->fileout))
	{
		if (!builtin(all, all->cmd->parsed))
			execution(all);
	}
	else if (all->cmd->parsedpipe || all->redir)
		pipe_commands(all, all->cmd, 1);
	return ;
}