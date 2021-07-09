/*#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

int sh_cd(char **args)
{
	if (args[1] == NULL)
		write(1, "sh: expected argument to cd\n", 29);
	else if (chdir(args[1]) != 0)
		strerror(errno);
	return (1);
}

int sh_pwd(char **args)
{

	
}

int sh_exit(char **args)
{
	return (0);
}*/