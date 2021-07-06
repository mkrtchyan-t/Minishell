#include "minishell.h"

void	execution(char *cmd)
{
	const char path[6][20] = {
		"/usr/local/bin",
		"/usr/bin",
		"/bin",
		"/usr/sbin",
		"/sbin",
		"/usr/local/munki"
	};
	int i = 0;
	int len;
	DIR *dir;
	int pid;
	struct dirent *dp;
	char *name = "ls"; // this variable is the same "cmd" which should pass by function argument
	char *newname = ft_strjoin("/", name);
	char *argv[] = {name, NULL};

	while (path[i])
	{
		if (!(dir = opendir(path[i])))
			exit (1);
		len = ft_strlen(name);
		while ((dp = readdir(dir)) != NULL)
		{
			if (dp->d_namlen == len && ft_strcmp(dp->d_name, name) == 0)
				{
					pid = fork();
					if (pid == 0)
					{
						if ((execve(ft_strjoin(path[i], newname), argv, NULL)) == -1)
							ft_putstr_fd("error while executing the command", 1);
					}
					exit(1);
				}
		}
		i++;
	}
	ft_putstr_fd("no such file or directory:(", 1);
}