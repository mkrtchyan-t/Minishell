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
	//for executing without pipe use
	/*
	if (all->cmd->parsed)
	{
		int i = 0;
		while (all->cmd->parsed[i] != NULL)
		{
			printf("%s", all->cmd->parsed[i]);
			i++;
		}
	}
	*/
	//with pipe use
	// if (!all->cmd->parsed)
	// {
	// 	while (all->cmd)
	// 	{
	// 		int i = 0;
	// 		while (all->cmd->parsedpipe[i] != NULL)
	// 		{
	// 			printf("%s ", all->cmd->parsedpipe[i]);
	// 			i++;
	// 		}
	// 		all->cmd = all->cmd->next;
	// 		printf("\n");
	// 	}
	// }
	// else
	// {
	// 	while (all->cmd)
	// 	{
	// 		int i = 0;
	// 		while (all->cmd->parsed[i] != NULL)
	// 		{
	// 			printf("%s\n", all->cmd->parsed[i]);
	// 			i++;
	// 		}
	// 		all->cmd = all->cmd->next;
	// 		printf("\n");
	// 	}
	// }
	/* all->cmd = all->cmd->next;
		where we use next for pipe, for example hello | hi, hello is parsedpipe[i] and then cmd->next
		after cmd ->next parsedpipe[i] is hi;, we use next for every pipe
	*/
}

int 	main(int args, char **argv, char **envp)
{
	char		*line;
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
	initenvp(&all, envp);
	// welcome_msg();
	while (1)
	{
		if (takeinput(&line))
			continue ;
		processline(line, &all);
		if (!(builtin(&all)))
			control_center(&all);
	}
}