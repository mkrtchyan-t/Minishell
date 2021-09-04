#include "minishell.h"

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	freecoms(t_all *all)
{
	int			i;
	t_commands	*tmp;

	if (all->coms && all->coms->piped == 1)
	{
		while (all->coms)
		{
			i = 0;
			while (all->coms->parsedpipe[i])
				free(all->coms->parsedpipe[i++]);
			i = 0;
			free(all->coms->parsedpipe);
			tmp = all->coms;
			all->coms = all->coms->next;
			free(tmp);
		}
	}
	else if (all->coms && all->coms->piped == 0)
	{
		i = 0;
		while (all->coms->parsed[i])
			free(all->coms->parsed[i++]);
		free(all->coms->parsed);
		free(all->coms);
		i = 0;
	}
}

void	freestrpiped(char **strpiped)
{
	int i;

	i = 0;
	while (strpiped[i])
		free(strpiped[i++]);
	free(strpiped);
}

void	freecmds(t_all *all)
{
	int			i;
	t_cmdfinal	*tmp;

	if (all->cmd && !all->cmd->parsed && all->cmd->parsedpipe)
	{
		while (all->cmd)
		{
			i = 0;
			if (all->cmd->parsedpipe)
			{	
				while (all->cmd->parsedpipe[i])
					free(all->cmd->parsedpipe[i++]);
				i = 0;
				free(all->cmd->parsedpipe);
			}
			tmp = all->cmd;
			all->cmd = all->cmd->next;
			free(tmp);
		}
	}
	else if (all->cmd && all->cmd->parsed)
	{
		i = 0;
		while (all->cmd->parsed[i])
			free(all->cmd->parsed[i++]);
		free(all->cmd->parsed);
		free(all->cmd);
		i = 0;
	}
	else if (all->cmd)
		free(all->cmd);
}

void freeredir(t_all *all)
{
	t_redirs *tmp;

	while (all->redir)
	{
		free(all->redir->filein);
		free(all->redir->fileout);
		tmp = all->redir;
		all->redir = all->redir->next;
		free(tmp);
	}
}

void freeheredoc(t_all *all)
{
	t_heredoc *tmp;

	while (all->here)
	{
		if (all->here->heredoc)
			free(all->here->heredoc);
		tmp = all->here;
		all->here = all->here->next;
		free(tmp);
	}
}
