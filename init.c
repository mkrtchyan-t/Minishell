#include "minishell.h"

void 	initfinal(t_cmdfinal *cmds)
{
	cmds->parsed = NULL;
	cmds->parsedpipe = NULL;
	cmds->next = NULL;
}

void 	initredirs(t_redirs *redir)
{
	redir->redir = 0;
	redir->file = NULL;
	redir->next = NULL;
}

char 	**copy_env(char **envp)
{
	int 	len;
	char 	**cpy;
	int 	i;

	len = 0;
	while (envp[len])
		len++;
	if (!(cpy = (char **)malloc(sizeof(char) * (len + 1))))
		return (0);
	i = 0;
	while (i < len)
	{
		cpy[i] = ft_strdup(envp[i]);
		i++;
	}
	return (cpy);
}

void	initcmds(t_commands *coms)
{
	coms->piped = 0;
	coms->parsed = NULL;
	coms->parsedpipe = NULL;
	coms->next = NULL;
}

void 	initenvp(t_envp *en, char **envp)
{
	en->envp = copy_env(envp);
}