#include "minishell.h"

int 	takeinput(char **line)
{
	char *buf;

	(void)line;
	buf = readline("$> ");
	if (ft_strlen(buf) != 0)
	{
		add_history(buf);
		*line = ft_strdup(buf);
		return (0);
	}
	return (1);
}

char 	**parsepipe(char *line)
{
	char **strpiped;

	strpiped = ft_split(line, '|');
	return(strpiped);
}

void 	parsespace(char *firstpart, char ***parsed)
{
	*parsed = ft_split(firstpart, ' ');
}

void	processline(char *line, t_all *all)
{
	char **strpiped;

	checkquotes(line);
	strpiped = NULL;
	strpiped = parsepipe(line);
	if (strpiped[1] != NULL)
		all->coms->piped = 1;
	if (all->coms->piped)
	{
		parsespace(strpiped[0], &all->coms->parsed);
		parsespace(strpiped[1], &all->coms->parsedpipe);
	}
	else
		parsespace(line, &all->coms->parsed);
	checkredirs(line, all);
	//for executing without pipe use all->cmd.parsed[0] 
	//and all->cmd.parsed[1] for argument, use all->cmd.parsedpipe[0]
	 //for pipe command and all->cmd.parsedpipe[1] for argument
}

int 	main(int args, char **argv, char **envp)
{
	char		*line;
	t_envp		en;
	t_all 		all;

	(void)argv;
	if (args != 1)
	{
		printf("\nError arguments");
		return (0);
	}
	line = NULL;
	all.coms = (t_commands *)malloc(sizeof(t_commands));
	if (!all.coms)
		exit(1);
	initcmds(all.coms);
	initfinal(&all.cmd);
	initenvp(&en, envp);
	//initredirs(&redir);
	welcome_msg();
	while (1)
	{
		if (takeinput(&line))
			continue ;
			processline(line, &all);
		if (!builtin(coms))
			if(!execution(coms->parsed))
			{
				ft_putstr_fd("shell: command not found", 1);
			}
	}
}