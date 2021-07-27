#include "minishell.h"

// echo +
// cd
// pwd +
// export
// unset
// env +
// exit +

int	env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	// printf("size: %d\n", i);
	return (i + 1);
}

char	**delete_arg(t_all *all, int i)
{
	int		j;
	char	**env;

	j = -1;

	env = (char **)malloc(sizeof(char) * (env_size(all->envp) - 1));
	while (++j < i)
	{
		env[j] = (char *)malloc(sizeof(char) * (ft_strlen(all->envp[j]) + 1));
		env[j] = ft_strdup(all->envp[j]);
		printf("\nPRINTF: %s\n\n", env[j]);
		printf("j: %d\n", j);
	}
	printf("mid j: %d\n", j);
	free(all->envp[i]);
	all->envp[i] = "\0";
	while(all->envp[++i])
	{
		env[j] = (char *)malloc(sizeof(char) * (ft_strlen(all->envp[i]) + 1));
		env[j] = ft_strdup(all->envp[i]);
		j++;
	}
	free(all->envp);
	return (env);
}

char	**unset(t_all *all)
{
	int		i;
	char	**env;

	i = 0;
	env = NULL;
	while (all->envp[i])
	{
		printf("envp: %s\n" , all->envp[i]);
		if (ft_strncmp(all->envp[i], all->cmd->parsed[1], ft_strlen(all->cmd->parsed[1])) == 0)
		{
			printf("i: %d\n", i);
			env = delete_arg(all, i);
			break ;
		}
		i++;
	}
	return (env);
}

int	cd(t_cmdfinal *cmd)
{
	char	*path;
	char	*tmp;

	if (cmd->parsed[1] == NULL)
	{
		if (chdir(getenv("HOME")) != 0)
			ft_putstr_fd("sh: cd: HOME not set", 1);
	}
	else
	{
		if (cmd->parsed[1][0] == 126)
		{
			tmp = ft_substr(cmd->parsed[1], 1, ft_strlen(cmd->parsed[1]) - 1);
			path = ft_strjoin(getenv("HOME"), tmp);
		}
		else
			path = cmd->parsed[1];
		if (chdir(path) != 0)
			perror(path);
		strerror(errno);
	}
	return (1);
}

void	pwd(void)
{
	char cwd[1024];

	getcwd(cwd, sizeof(cwd));
	ft_putstr_fd(cwd, 1);
}

void	print_env(t_all *all)
{
	int 	i;

	i = 0;
	if (all->cmd->parsed[1])
	{
		write(1, "env: ", 5);
		write(1, all->cmd->parsed[1], 1024);
		write(1, ": Permission denied\n", 20);
		return ;
	}
	while (all->envp[i])
		ft_putstr_fd(all->envp[i++], 1);
}

void	var_check(t_all *all, int *i)
{
	char	*tmp;

	if (all->cmd->parsed[*i][0] == '$')
	{
		if (!all->cmd->parsed[*i][1])
		{
			ft_putstr_fd(getenv(all->cmd->parsed[++(*i)]), 1);
		}
		else
		{
			tmp = all->cmd->parsed[*i];
			tmp++;
			printf("tmp: %s\n", tmp);
			ft_putstr_fd(getenv(tmp), 1);
		}
	}
	i++;
	all->return_val = errno;
}

void	echo_helper(t_all *all, int *fd)
{
	int		i;
	int		size;

	if (!all->cmd->parsed[1])
	{
		write(*fd, "\n", 1);
		return ;
	}
	size = cmdline_size(all->cmd->parsed);
	if (all->cmd->parsed[1] && (ft_strcmp(all->cmd->parsed[1], "-n")) == 0)
		i = 1;
	else
		i = 0;
	while(++i < size)
	{
		var_check(all, &i);
		printf("i: %d\n", i);
		if (ft_strcmp(all->cmd->parsed[i], "$?") == 0)
			ft_putnbr_fd(all->return_val, *fd);
		else
			write(*fd, all->cmd->parsed[i], ft_strlen(all->cmd->parsed[i]));
		if (all->cmd->parsed[i + 1])
			write(*fd, " ", 1);
	}
	if (ft_strcmp(all->cmd->parsed[1], "-n") != 0)
	write(*fd, "\n", 1);
}

void	echo(t_all *all)
{
	int		fd;
	t_all	*tmp;

	fd = 1;
	tmp = all;
	if (!all->redir)
	{
		echo_helper(all, &fd);
	}
	else if (all->redir->fileout)
	{
		fd = (all->redir->typefileout == 1) ?
				(open(all->redir->fileout, O_WRONLY | O_TRUNC | O_CREAT, 0644)) :
				(open(all->redir->fileout, O_WRONLY | O_APPEND | O_CREAT, 0644));
		if (fd == -1)
			perror(all->redir->fileout);
		echo_helper(all, &fd);
	}
	all->return_val = errno;
}

int	builtin(t_all *all)
{
	int i;

	i = 0;
	while (all->cmd->parsed[i])
	{
		if (ft_strcmp(all->cmd->parsed[i], "pwd") == 0)
		{
			pwd();
			return (1);
		}
		else if (ft_strcmp(all->cmd->parsed[i], "cd") == 0)
		{
			// ft_putstr_fd("i still dont work:)", 1);
			cd(all->cmd);
			return (1);
		}
		else if (ft_strcmp(all->cmd->parsed[i], "exit") == 0)
		{
			// goodbye_msg();
			exit(0);
		}
		else if (ft_strcmp(all->cmd->parsed[i], "echo") == 0)
		{
			echo(all);
			return (1);
		}
		else if (ft_strcmp(all->cmd->parsed[i], "export") == 0)
		{
			ft_putstr_fd("i still dont work:)", 1);
			return (1);
		}
		else if (ft_strcmp(all->cmd->parsed[i], "unset") == 0)
		{
			// ft_putstr_fd("i still dont work:)", 1);
			all->envp = unset(all);
			return (1);
		}
		else if (ft_strcmp(all->cmd->parsed[i], "env") == 0)
		{
			print_env(all);
			return (1);
		}
		i++;
	}
	return (0);
}