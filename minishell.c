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

void	processline(char *line, t_commands *coms, t_redirs *redir)
{
	char **strpiped;

	checkquotes(line);
	checkredirs(redir, line);
	strpiped = NULL;
	strpiped = parsepipe(line);
	if (strpiped[1] != NULL)
		coms->piped = 1;
	if (coms->piped)
	{
		parsespace(strpiped[0], &coms->parsed);
		parsespace(strpiped[1], &coms->parsedpipe);
	}
	else
		parsespace(line, &coms->parsed);
	// printf("%s", coms->parsed[0]);
	//builtin handler... it must return 0 if it's builtin 
	//1 is simple command, 2 if pipe
	//for executing without pipe use coms->parsed[0] 
	//and coms->parsed[1] for argument, use parsedpipe for pipe
	// printf("parsed: %s\t%s\t%s\n", coms->parsed[0], coms->parsed[1], coms->parsed[2]);
}

int 	main(int args, char **argv, char **envp)
{
	char		*line;
	t_commands	*coms;
	t_envp		en;
	t_redirs	redir;

	(void)argv;
	if (args != 1)
	{
		printf("\nError arguments");
		return (0);
	}
	line = NULL;
	coms = (t_commands *)malloc(sizeof(t_commands));
	if (!coms)
		exit(1);
	initcmds(coms);
	initenvp(&en, envp);
	//initredirs(&redir);
	welcome_msg();
	while (1)
	{
		if (takeinput(&line))
			continue ;
			processline(line, coms, &redir);
		if (!builtin(coms))
			if(!execution(coms->parsed))
			{
				ft_putstr_fd("shell: command not found", 1);
			}
	}
}