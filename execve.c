#include "minishell.h"

// void	make_array(t_cmdfinal *cmd)
// {
// 	int			i;
// 	int			size;
// 	char		**array;
// 	t_cmdfinal	*tmp;

// 	tmp = cmd;
// 	i = 0;
// 	size = cmd_size(cmd);
// 	printf("cmd size: %d\n", size);
// 	if (!(array = (char **)malloc(sizeof(char) * (size + 1))))
// 		exit (1);
// 	while (cmd->parsed)
// 	{
// 		array[i] = malloc(sizeof(char) * ft_strlen(cmd->parsed));
// 		array[i] = cmd->parsed;
// 		cmd->parsed = cmd->next;
// 		printf("array[%d]: %s\n", i, array[i]);
// 		i++;
// 	}
// 	array[i] = NULL;
// 	cmd = tmp;
// }

int	execution(t_all *all)
{
	char	**path;
	int		i;
	int		len;
	DIR		*dir;
	int		pid;
	struct	dirent *dp;
	char	*newname;

	i = 0;
	newname = ft_strjoin("/", all->cmd->parsed[0]);
	path = ft_split(getenv("PATH"), ':');
	while (path[i])
	{
		if (!(dir = opendir(path[i])))
			exit (1);
		len = ft_strlen(all->cmd->parsed[0]);
		while ((dp = readdir(dir)) != NULL)
		{
			if (dp->d_namlen == len && ft_strcmp(dp->d_name, all->cmd->parsed[0]) == 0)
			{
				pid = fork();
				if (pid == 0)
				{
					if ((execve(ft_strjoin(path[i], newname), all->cmd->parsed, NULL)) == -1)
						perror(all->cmd->parsed[0]);
					return (0);
				}
				else if (pid < 0)
					ft_putstr_fd("sh: process error", 1);
				else
					wait(0);
			}
		}
		i++;
	}
	free(path);
	closedir(dir);
	return (1);
}

// int	execution_pipe(t_all *all)
// {
// 	all = all + 1;
// 	return (1);
// }

void	control_center(t_all *all)
{
	if (!all->cmd->parsedpipe)
		execution(all);
	// else
	// 	execution_pipe(all);
}