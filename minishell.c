#include "minishell.h"

int	takeinput(char **line)
{
	char *buf;

	buf = readline("\033[1;34mminishell\033[0;0m$> ");
	if (buf && ft_strlen(buf) != 0)
	{
		add_history(buf);
		*line = ft_strdup(buf);
		return (0);
	}
	else if (buf == NULL)
		return (2);
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
	int 	i;
	char 	**str;

	i = 0;
	str = ft_splitline(firstpart, ' ');
	while (str[i] != NULL)
		i++;
	checkdolar(str, all);
	*parsed = str;
}

int	processline(char *line, t_all *all)
{
	char 		**strpiped;
	int 		i;
	t_commands 	*new;

	i = 0;
	new = NULL;
	all->coms = NULL;
	new = malloc(sizeof(t_commands));
	if (!checkquotes(line))
	{
		ft_putstr_fd(1, "unclosed quotes", 1);
		return (0);
	}
	initcmds(new);
	strpiped = NULL;
	strpiped = parsepipe(line);
	if (strpiped[1] != NULL)
		new->piped = 1;
	if (new->piped)
	{	
		i = 0;
		while (strpiped[i])
		{
			parsespace(strpiped[i], &new->parsedpipe, all);
			addbackcom(&all->coms, new);
			new = malloc(sizeof(t_commands));
			initcmds(new);
			new->piped = 1;
			i++;
		}
	}
	else
	{
		parsespace(line, &new->parsed, all);
		addbackcom(&all->coms, new);
	}
	checkredirs(line, all);
	//for executing without pipe and
	//with pipe use
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
	/*while(all->redir)
	{
	 	printf("%d: fileintype: %d  fileouttype: %d  fileout:%s\n  filein:%s\n", all->redir->redir, all->redir->typefilein, \
	 			all->redir->typefileout, all->redir->fileout, all->redir->filein);
	 	all->redir = all->redir->next;
	}*/
	return (1);
}

static void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		// ft_putstr_fd(0, "\033[12C\033[0K\n", 1);
		// ft_putstr_fd(0, "\r\033[1;34mminishell\033[0;0m$> ", 1);
	}
}

int	main(int args, char **argv, char **envp)
{
	char		*line;
	t_all		all;
	int 		input;

	(void)argv;
	if (args != 1)
	{
		ft_putstr_fd(1, "Error: too many arguments", 1);
		return (0);
	}
	line = NULL;
	all.coms = (t_commands *)malloc(sizeof(t_commands));
	if (!all.coms)
		exit(1);
	initcmds(all.coms);
	initenvp(&all, envp);
	signal(SIGQUIT, SIG_IGN);
	// welcome_msg();
	while (1)
	{
		signal(SIGINT, sig_handler);
		input = takeinput(&line);
		if (input == 1)
			continue ;
		else if (input == 2)
			break ;
		if (!all_space(line))
		{
			if (!processline(line, &all))
				continue ;
		}
		else
			continue ;
		control_center(&all);
	}
}
