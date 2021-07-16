#include "libft/libft.h"
#include "get_next_line/get_next_line.h"
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

typedef struct 	s_redirects
{
	int 				redir;
	int 				type; // 1 for in 2 for out
	char 				*file;
	struct s_redirects 	*next;
}				t_redirs;

typedef	struct 	s_envp
{
	char **envp;
}				t_envp;

typedef	struct 	s_cmdfinal
{
	char 	**parsed;
	char 	**parsedpipe;
}				t_cmdfinal;

typedef struct 	s_all
{
	t_commands 	*coms;
	t_redirs	redir;
	t_cmdfinal 	cmd;
}				 t_all;

void		initcmds(t_commands *coms);
void 		checkquotes(char *line);
void 		initenvp(t_envp *en, char **envp);
int			execution(char **cmd);
int			builtin(t_commands *cmd);
void		goodbye_msg();
void		welcome_msg();
void 		initredirs(t_redirs *redir);
int			addback(t_redirs **a, t_redirs *new);
t_redirs	*last(t_redirs *lst);
void 		initfinal(t_cmdfinal *cmds);
void 		checkredirs(char *line, t_all *all);

