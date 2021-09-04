#include "minishell.h"

int	takeinput(char **line)
{
	char *buf;

	buf = readline("minishell$> ");
	if (buf && ft_strlen(buf) != 0)
	{
		add_history(buf);
		*line = ft_strdup(buf);
		free(buf);
		return (0);
	}
	else if (buf == NULL)
		return (2);
	free(buf);
	return (1);
}

char	**parsepipe(char *line)
{
	char **strpiped;

	strpiped = ft_splitline(line, '|');
	return(strpiped);
}

void	parsespace(char *firstpart, char ***parsed, t_all *all)
{
	int		i;
	char	**str;

	i = 0;
	str = ft_splitline(firstpart, ' ');
	i = 0;
	while (str[i] != NULL)
	{
		checkdolar(&str[i], all);
		i++;
	}
	*parsed = str;
}

int	processline(char *line, t_all *all)
{
	char		**strpiped;
	int			i;
	t_commands	*new;
	int			piped;
	int			ret;

	i = 0;
	new = NULL;
	all->here = NULL;
	all->coms = NULL;
	if ((ret = checkquotes(line)))
	{
		if (ret == 1)
		{
			ft_putstr_fd(1, "unclosed quotes", 1);
			return (0);
		}
		else if (ret == 2)
		{
			ft_putstr_fd(1, "> ", 1);
			return (0);
		}
		else if (ret == 3)
		{
			ft_putstr_fd(1, "sh: syntax error near unexpected token `|'", 2);
			return (0);
		}
	}
	piped = 0;
	strpiped = NULL;
	strpiped = parsepipe(line);
	if (strpiped[1] != NULL)
		piped = 1;
	if (piped)
	{
		i = 0;
		while (strpiped[i])
		{
			new = malloc(sizeof(t_commands));
			initcmds(new);
			new->piped = 1;
			parsespace(strpiped[i], &new->parsedpipe, all);
			addbackcom(&all->coms, new);
			i++;
		}
	}
	else
	{
		new = malloc(sizeof(t_commands));
		initcmds(new);
		parsespace(line, &new->parsed, all);
		addbackcom(&all->coms, new);
	}
	freestrpiped(strpiped);
	checkredirs(line, all);
	freecoms(all);
	//for executing without pipe and
	//with pipe use
	//printf("%p", all->cmd);
	/*if (!all->cmd->parsed && all->cmd->parsedpipe)
	{
		while (all->cmd)
	 	{
	 		int i = 0;
	 		while (all->cmd->parsedpipe[i] != NULL)
	 		{
				printf("%s\n", all->cmd->parsedpipe[i]);
	 			i++;
	 		}
	 		all->cmd = all->cmd->next;
	 		printf("\n");
	 	}
	 }
	else if (all->cmd->parsed)
	 {
		 while (all->cmd)
		 {
		 	int i = 0;
		 	while (all->cmd->parsed[i] != NULL)
		 	{
		 		printf("%s\n", all->cmd->parsed[i]);
		 		i++;
		 	}
		 	all->cmd = all->cmd->next;
		 	printf("\n");
		 }
	 }*/
	/* all->cmd = all->cmd->next;
		where we use next for pipe, for example hello | hi, hello is parsedpipe[i] and then cmd->next
		after cmd ->next parsedpipe[i] is hi;, we use next for every pipe
	*/
	//for redir - filetypes - 1 for < or >, 2 for << or >>
	//printf("%p", all->redir);
	/*while (all->here)
	{
		printf("%s\n", all->here->heredoc);
		all->here = all->here->next;
	}*/
	/*while(all->redir)
	{
	 	printf("%d: fileintype: %d  fileouttype: %d redir: %d  fileout:%s\n  filein:%s\n", all->redir->redir, all->redir->typefilein, \
	 			all->redir->typefileout, all->redir->redir,  all->redir->fileout, all->redir->filein);
	 	printf("%p\n", all->redir);
	 	all->redir = all->redir->next;
	}*/
	return (1);
}

static void	sig_handler(int sig)
{
	if (sig == SIGINT && !g_glob.forked)
	{
		write(1, "\r", 1);
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd(0, "  \b\b", 1);
	}
	if (sig == SIGINT && !g_glob.forked)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		*(g_glob.ret) = 1;
	}
	else if (sig == SIGINT && g_glob.forked && !g_glob.here)
	{
		write(1, "\n", 1);
		*(g_glob.ret) = 130;
	}
	else if (sig == SIGINT && g_glob.forked && g_glob.here)
	{
		write(1, "\b\b  \b\b", 6);
		write(1, "\n", 1);
	}
	else if (sig == SIGQUIT && g_glob.forked)
	{
		*(g_glob.ret) = 131;
		printf("Quit: 3\n");
	}
}

int	main(int args, char **argv, char **envp)
{
	char		*line;
	t_all		all;
	int			input;

	(void)argv;
	if (args != 1)
	{
		ft_putstr_fd(1, "Error: too many arguments", 1);
		return (0);
	}
	line = NULL;
	signal(SIGQUIT, SIG_IGN);
	g_glob.ret = &(all.return_val);
	initenvp(&all, envp);
	g_glob.here = 0;
	while (1)
	{
		g_glob.forked = 0;
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
		input = takeinput(&line);
		if (input == 1)
			continue ;
		else if (input == 2)
			break ;
		if (!all_space(line))
		{
			if (!processline(line, &all))
			{
				free(line);
				continue ;
			}
		}
		else
		{
			free(line);
			continue ;
		}
		control_center(&all);
		free(line);
		freecmds(&all);
		freeredir(&all);
		freeheredoc(&all);
	}
}
