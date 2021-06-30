#include "minishell.h"

t_builtins g_builtins;

void 	initstruct(t_builtins *g_builtins)
{
	g_builtins->bins = {

		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
	};
	g_builtins->count = 7;

}

int 	sh_execute(char **args)
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
}

int 	main()
{
	int 	status;
	char 	*line;
	char 	**args;

	initstruct(&g_builtins);
	status = 1;
	while (status)
	{
		write(1, ">$ ". 3);
		get_next_line(0, &line);
		args = ft_split(line, ' ');
		status = sh_execute(args);
		free(line);
		free(args);
	}
}