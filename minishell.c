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

void 	processline(char *line, t_commands *coms)
{
	char **strpiped;

	strpiped = NULL;
	strpiped = parsepipe(line);
	if (strpiped[1] != NULL)
		coms->piped = 1;
}

/*int 	sh_execute(char **args)
{
	int i;

	i = 0;
	if (args[0] == NULL)
		return (1);
	while (i < g_builtins.count)
	{
		if (ft_strcmp(args[0], g_builtins.bins[i]))
			//

	}
}*/

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