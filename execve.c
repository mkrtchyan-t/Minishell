#include "minishell.h"

int		execution(char **cmd)
{
	char *env;
	char **path;
	int i = 0;
	int len;
	DIR *dir;
	int pid;
	struct dirent *dp;
	char *newname = ft_strjoin("/", cmd[0]);
	char *argv[] = {cmd[0], NULL};

	// char cwd[1024];
	// getcwd(cwd, sizeof(cwd));
	// ft_putstr_fd(cwd, 1);

	env = getenv("PATH");
	path = ft_split(env, ':');
	while (path[i])
	{
		if (!(dir = opendir(path[i])))
			exit (1);
		len = ft_strlen(cmd[0]);
		while ((dp = readdir(dir)) != NULL)
		{
			if (dp->d_namlen == len && ft_strcmp(dp->d_name, cmd[0]) == 0)
			{
				pid = fork();
				if (pid == 0)
				{
					if ((execve(ft_strjoin(path[i], newname), argv, NULL)) == -1)
						ft_putstr_fd("error while executing the command", 1);
				}
			}
		}
		i++;
	}
	closedir(dir);
	return (1);
}