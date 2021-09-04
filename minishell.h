#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <errno.h>
# include <termios.h>
# include <fcntl.h>

typedef struct s_glob
{
	int forked;
	int *ret;
	int here;
}	t_glob;

t_glob g_glob;

typedef struct s_commands
{
	int					piped;
	char				**parsed;
	char				**parsedpipe;
	struct s_commands	*next;
}	t_commands;

typedef struct s_redirects
{
	int					redir;
	char				*filein;
	char				*fileout;
	int					typefilein;
	int					typefileout;
	struct s_redirects	*next;
}	t_redirs;

typedef struct s_cmdfinal
{
	char				**parsed;
	char				**parsedpipe;
	struct s_cmdfinal	*next;
}	t_cmdfinal;


typedef struct 	s_heredoc
{
	char 				*heredoc;
	struct s_heredoc 	*next;
	char 				*file;

}				t_heredoc;

typedef struct s_all
{
	t_commands	*coms;
	t_redirs	*redir;
	t_cmdfinal	*cmd;
	char		**envp;
	int			return_val;
	t_heredoc 	*here;
}	t_all;

void		initcmds(t_commands *coms);
void		initenvp(t_all *all, char **envp);
int			execution(t_all *all);
int			execution_pipe(t_all *all);
int			builtin(t_all *all, char **arg);
void		goodbye_msg(void);
void		welcome_msg(void);
void		initredirs(t_redirs *redir);
int			addback(t_redirs **a, t_redirs *neww);
t_redirs	*last(t_redirs *lst);
void		initfinal(t_cmdfinal *cmds);
void		checkredirs(char *line, t_all *all);
int			addbackcom(t_commands **a, t_commands *neww);
int			addbackcmd(t_cmdfinal **a, t_cmdfinal *neww);
void		control_center(t_all *all);
int			cmd_size(t_cmdfinal *cmd);
int			cmdline_size(char **cmd);
void		echo(t_all *all, char **arg);
char		**unset(t_all *all, char **arg);
int			env_size(char **env);
int			cd(t_all *all, char **arg);
int			pwd(void);
void		print_env(t_all *all);
char		**export_(t_all *all, char **arg);
void		ft_setenv(char **envp, char *value, char *key);
char		*ft_getenv(char **envp, char *var);
size_t		ft_strclen(char *str, int c);
int			has_value(char *env);
char		**ft_splitline(char const *s, char c);
void		pipe_commands(t_all *all, t_cmdfinal *command, int p_count);
char		*get_cmd(t_all *all);
int			all_space(char *line);
void		child_sig_handler(int sig);
void		child_sig_handler_bash(int sig);
char		*trimquotes(char *str);
int			insquotes(char const *str, int index);
int			indquotes(char const *str, int index);
int			checkquotes(char *line);
void		checkdolar(char **str, t_all *all);
char		**checkcommand(t_all *all, char **str);
void		heredoc(t_all *all);
int			inquotes(char const *str, int index);
char		*join(char *f, char c);
void		ft_error(char *str, t_all *all);
void		ft_simplerror(char *str, t_all *all);
char		**copy_env(char **envp);
void		initheredoc(t_heredoc *here);
char		*replacequest(char *str, int start, int end, t_all *all);
char		*replacestr(char *str, int start, int end, t_all *all);

// free functions
void		free_envp(char **envp);
void		freeredir(t_all *all);
void		freeheredoc(t_all *all);
void		freecmds(t_all *all);
void		freecoms(t_all *all);
void		freestrpiped(char **strpiped);

#endif