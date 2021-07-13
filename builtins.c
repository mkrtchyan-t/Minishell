#include "minishell.h"

// echo
// cd
// pwd
// export
// unset
// env
// exit

int sh_cd(char *cmd)
{
	if (cmd == NULL)
	{
		if (chdir("HOME") != 0)
			strerror(errno);
	}
	else if (chdir(cmd) != 0)
		strerror(errno);
	return (1);
}

void sh_pwd(void)
{
	char cwd[1024];

	getcwd(cwd, sizeof(cwd));
	ft_putstr_fd(cwd, 1);
}

int sh_exit(void)
{
	exit(0);
}

int	builtin(t_commands *cmd)
{
	int i;

	i = 0;
	while (cmd->parsed[i])
	{
		if (ft_strcmp(cmd->parsed[i], "pwd") == 0)
		{
			sh_pwd();
			return (1);
		}
		else if (ft_strcmp(cmd->parsed[i], "cd") == 0)
		{
			sh_cd(cmd->parsed[i]);
		}
		else if (ft_strcmp(cmd->parsed[i], "exit") == 0)
		{
			sh_exit();
		}
		else
		{
			return (0);
		}
	}
	return (0);
}