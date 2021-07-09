#include "minishell.h"

void	initcmds(t_commands *coms)
{
	coms->piped = 0;
	coms->parsed = NULL;
	coms->parsedpipe = NULL;
}