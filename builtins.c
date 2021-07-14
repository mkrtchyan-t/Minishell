#include "minishell.h"

// echo
// cd
// pwd +
// export
// unset
// env
// exit +

int sh_cd(t_commands *cmd)
{
	if (cmd->parsed[1] == NULL)
	{
		if (chdir("~/") != 0)
			strerror(errno);
	}
	else if (chdir("get_next_line") != 0)
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
			ft_putstr_fd("i still dont work:)", 1);
			// sh_cd(cmd);
			return (1);
		}
		else if (ft_strcmp(cmd->parsed[i], "exit") == 0)
		{
			goodbye_msg();
			sh_exit();
			return (1);
		}
		else if (ft_strcmp(cmd->parsed[i], "echo") == 0)
		{
			ft_putstr_fd("i still dont work:)", 1);
			return (1);
		}
		else if (ft_strcmp(cmd->parsed[i], "export") == 0)
		{
			ft_putstr_fd("i still dont work:)", 1);
			return (1);
		}
		else if (ft_strcmp(cmd->parsed[i], "unset") == 0)
		{
			ft_putstr_fd("i still dont work:)", 1);
			return (1);
		}
		else if (ft_strcmp(cmd->parsed[i], "env") == 0)
		{
			ft_putstr_fd("i still dont work:)", 1);
			return (1);
		}
		i++;
	}
	return (0);
}