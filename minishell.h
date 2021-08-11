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

typedef struct s_all
{
	t_commands	*coms;
	t_redirs	*redir;
	t_cmdfinal	*cmd;
	char		**envp;
	int			return_val;
}	t_all;

void		initcmds(t_commands *coms);
void		checkquotes(char *line);
void		initenvp(t_all *all, char **envp);
int			execution(t_all *all);
int			execution_pipe(t_all *all);
int			builtin(t_all *all);
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
int			echo(t_all *all);
char		**unset(t_all *all);
int			env_size(char **env);
int			cd(t_all *all);
int			pwd(void);
void		print_env(t_all *all);
char		**export_(t_all *all);
void		ft_setenv(char **envp, char *value, char *key);
char		*ft_getenv(char **envp, char *var);
size_t		ft_strclen(char *str, int c);
int			has_value(char *env);
char		**ft_splitline(char const *s, char c);
void		pipe_commands(t_all *all, t_cmdfinal *command, int p_count);
int			ft_execve(t_all *all);
char		*get_cmd(t_all *all);
int			all_space(char *line);
void		child_sig_handler(int sig);
void		child_sig_handler_bash(int sig);


// free functions
void		free_envp(char **envp);

#endif