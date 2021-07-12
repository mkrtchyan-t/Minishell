#include "minishell.h"

int 	takeinput(char **line)
{
	char *buf;

	(void)line;
	buf = readline("\n$> ");
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

void 	processline(char *line, t_commands *coms)
{
	char **strpiped;

	checkquotes(line);
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
	printf("%s", coms->parsed[0]);
	//builtin handler... it must return 0 if it's builtin 
	//1 is simple command, 2 if pipe
	//for executing without pipe use coms->parsed[0] 
	//and coms->parsed[1] for argument, use parsedpipe for pipe
}

int 	main(int args, char **argv, char **envp)
{
	char 		*line;
	t_commands 	coms;
	t_envp		en;

	(void)argv;
	if (args != 1)
	{
		printf("\nError arguments");
		return (0);
	}
	line = NULL;
	initcmds(&coms);
	initenvp(&en, envp);
	while (1)
	{
		if (takeinput(&line))
			continue ;
		processline(line, &coms);
	}
}