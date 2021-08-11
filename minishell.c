#include "minishell.h"

int	takeinput(char **line)
{
	char *buf;

	(void)line;
	buf = readline("\033[1;34mminishell\033[0;0m$> ");
	if (ft_strlen(buf) != 0)
	{
		add_history(buf);
		*line = ft_strdup(buf);
		return (0);
	}
	return (1);
}

char	**parsepipe(char *line)
{
	char **strpiped;

	strpiped = ft_split(line, '|');
	return(strpiped);
}

void	parsespace(char *firstpart, char ***parsed)
{
	*parsed = ft_splitline(firstpart, ' ');
}

void	processline(char *line, t_all *all)
{
	char 		**strpiped;
	int 		i;
	t_commands 	*new;

	i = 0;
	new = NULL;
	all->coms = NULL;
	new = malloc(sizeof(t_commands));
	checkquotes(line);
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
			parsespace(strpiped[i], &new->parsedpipe);
			addbackcom(&all->coms, new);
			new = malloc(sizeof(t_commands));
			initcmds(new);
			new->piped = 1;
			i++;
		}
	}
	else
	{
		parsespace(line, &new->parsed);
		addbackcom(&all->coms, new);
	}
	checkredirs(line, all);
	//for executing without pipe and
	//with pipe use
	/*if (!all->cmd->parsed)
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
	 else
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
}

static void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd(0, "\033[12C\033[0K\n", 1);
		ft_putstr_fd(0, "\r\033[1;34mminishell\033[0;0m$> ", 1);
	}
	if (sig == SIGQUIT)
		ft_putstr_fd(0, "\033[12C\033[0K", 1);
}

int	main(int args, char **argv, char **envp)
{
	char		*line;
	t_all		all;

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
	signal(SIGQUIT, sig_handler);
	// welcome_msg();
	while (1)
	{
		signal(SIGINT, sig_handler);
		if (takeinput(&line))
			continue ;
		if (!all_space(line))
			processline(line, &all);
		else
			continue ;
		control_center(&all);
	}
}
