#include "libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef	struct 	s_commmands
{
	int 	piped;
	char 	**parsed;
	char 	**parsedpipe;
}				t_commands;


void	initcmds(t_commands *coms);