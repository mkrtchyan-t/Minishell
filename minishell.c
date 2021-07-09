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
	printf("%s", coms->parsedpipe[1]);
	//builtin handler... it must return 0 if it's builtin 
	//1 is simple command, 2 if pipe
	//for executing without pipe use coms->parsed[0] \
	and coms->parsed[1] for argument, use parsedpipe for pipe
}

int 	main()
{
	char 		*line;
	t_commands 	coms;

	line = NULL;
	initcmds(&coms);
	while (1)
	{
		if (takeinput(&line))
			continue ;
		processline(line, &coms);
	}
}