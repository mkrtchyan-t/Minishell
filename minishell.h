#include "libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>

typedef	struct 	s_commmands
{
	int 	piped;
	char 	**parsed;
	char 	**parsedpipe;
}				t_commands;

typedef	struct 	s_envp
{
	char **envp;
}				t_envp;



void	initcmds(t_commands *coms);
void 	checkquotes(char *line);
void 	initenvp(t_envp *en, char **envp);
int		execution(char **cmd);
int		builtin(t_commands *cmd);