#include "minishell.h"

int	ft_isspace(char c)
{
	return (c == '\t' || c== '\n' || c== '\v' || c== '\f' \
			|| c== '\r' || c == ' ');
}

void	checkredirsout(t_redirs **redir, char *line)
{
	int			i;
	t_redirs	*new;
	int			type;
	char		*tmp;

	new = NULL;
	i = 0;
	while (line[i] != '\0')
	{
		type = ((line[i] == '>' && line[i + 1] == '>') ? 2: 0);
		if (((line[i] == '>' && line[i + 1] == '>') || \
			(line[i] == '>' && line[i + 1] != '>')) && !inquotes(line, i))
		{
			if (type == 2 && line[i + 2] == '>')
				return ;
			new = (t_redirs *)malloc(sizeof(t_redirs));
			initredirs(new);
			new->redir = 1;
			new->fileout = ft_strdup("");
			new->typefileout = (type == 2) ? 2: 1;
			while (line[i] == '>' && line[i])
				i++;
			while (ft_isspace(line[i]) && line[i])
				i++;
			while (!ft_isspace(line[i]) && line[i] != '>' && line[i] != '<' && line[i])
			{
				tmp = new->fileout;
				new->fileout = join(new->fileout, line[i]);
				free(tmp);
				i++;
			}
			i--;
		}
		i++;
	}
	if (new)
	{
		if (ft_strcmp(new->fileout, "") != 0)
			addback(redir, new);
		else
		{
			free(new->fileout);
			free(new);
		}
	}
	else
	{
		new = (t_redirs *)malloc(sizeof(t_redirs));
		initredirs(new);
		addback(redir, new);
	}
}

void	checkredirsin(t_redirs **redir, char *line, t_all *all)
{
	int			i;
	t_redirs	*new;
	t_redirs	*tmp;
	int			type;
	char		*tmp2[2];
	t_heredoc	*tm[3];

	new = NULL;
	i = 0;
	tm[1] = NULL;
	tm[0] = NULL;
	while (line[i] != '\0')
	{
		type = (line[i] == '<' && line[i + 1] == '<') ? 2: 0;
		if (((line[i] == '<' && line[i + 1] == '<') || \
			(line[i] == '<' && line[i + 1] != '<')) && !inquotes(line, i))
		{
			if (new)
			{
				free(new->filein);
				free(new);
			}
			if (type == 2 && line[i + 2] == '<')
				return ;
			new = (t_redirs *)malloc(sizeof(t_redirs));
			initredirs(new);
			new->redir = 1;
			new->filein = ft_strdup("");
			new->typefilein = (type == 2) ? 2: 1;
			while (line[i] == '<' && line[i])
				i++;
			while (ft_isspace(line[i]) && line[i])
				i++;
			if (new->typefilein == 2)
			{
				tm[0] = (t_heredoc *)malloc(sizeof(t_heredoc));
				initheredoc(tm[0]);
				tm[0]->heredoc = ft_strdup("");
			}
			while (!ft_isspace(line[i]) && line[i] != '<' && line[i] != '>' && line[i])
			{
				if (new->typefilein == 2)
				{
					tmp2[1] = tm[0]->heredoc;
					tm[0]->heredoc = join(tm[0]->heredoc, line[i]);
					free(tmp2[1]);
				}
				tmp2[0] = new->filein;
				new->filein = join(new->filein, line[i]);
				free(tmp2[0]);
				i++;
			}
			if (new->typefilein == 2 && ft_strcmp(tm[0]->heredoc, "") != 0)
			{
				if (!all->here)
				{
					all->here = tm[0];
					tm[1] = all->here;
				}
				else
				{
					tm[1] = all->here;
					while (all->here->next)
						all->here = all->here->next;
					all->here->next = tm[0];
					all->here = tm[1];
				}
			}
			else if (new->typefilein == 2)
			{
				free(tm[0]->heredoc);
				free(tm[0]);
			}
			i--;
		}
		i++;
	}
	if (tm[1])
		all->here = tm[1];
	if (*redir != NULL && new)
	{
		tmp = *redir;
		while ((*redir)->next != NULL)
			*redir = (*redir)->next;
		(*redir)->filein = ft_strdup(new->filein);
		(*redir)->typefilein = new->typefilein;
		*redir = tmp;
	}
	else if (new)
	{
		if (ft_strcmp(new->filein, "") != 0)
			addback(redir, new);
		else
		{
			free(new->filein);
			free(new);
		}
	}
	else if (!new && *redir == NULL)
	{
		new = (t_redirs *)malloc(sizeof(t_redirs));
		initredirs(new);
		addback(redir, new);
	}
}

static int	inquote(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!inquotes(str, i))
			return (0);
		i++;
	}
	return (1);
}

int	checkmalloc(char **str, t_all *all)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	checksingle(char **str, t_all *all, int start, int i)
{
	if (str[i][start] && ((str[i][start] == '<' && str[i][start + 1] == '<') \
		|| (str[i][start] == '>' && str[i][start + 1] == '>') ||
		(str[i][start] == '<' && str[i][start + 1] != '<') \
		|| (str[i][start] == '>' && str[i][start + 1] != '>')) && !inquotes(str[i], start))
	{
		if (str[i][start] == '>')
		{
			if (!all->redir || (all->redir && !all->redir->fileout))
			{
				ft_putstr_fd(1, "sh: syntax error near unexpected token `newline'", 1);
				all->return_val = 258;
				return (0) ;
			}
		}
		else if (str[i][start] == '<')
		{
			if (!all->redir || (all->redir && !all->redir->filein))
			{
				ft_putstr_fd(1, "sh: syntax error near unexpected token `newline'", 1);
				all->return_val = 258;
				return (0);
			}
		}
	}
	return (1);
}

char	**checkcommand(t_all *all, char **str)
{
	int		i;
	char	**cmd;
	int		j;
	int		done;
	int		start;
	char	*st;
	int		l;

	j = 0;
	i = 0;
	done = 0;
	start = 0;
	cmd = malloc(sizeof(char *) * (checkmalloc(str, all) + 1));
	i = 0;
	while (str[i])
	{
		start = 0;
		st = (char *)malloc(sizeof(char) * (ft_strlen(str[i]) + 1));
		while (str[i][start] && ((str[i][start] != '>' && str[i][start] != '<') || inquotes(str[i], start)))
		{
			st[start] = str[i][start];
			start++;
		}
		st[start] = '\0';
		if (!checksingle(str, all, start, i))
		{
			l = 0;
			while (l < j)
			{
				free(cmd[l]);
				l++;
			}
			free(st);
			done = 0;
			break ;
		}
		if (((ft_strcmp(str[i], ">") == 0) || (ft_strcmp(str[i], ">>") == 0)\
			|| ft_strcmp(str[i], "<") == 0 || ft_strcmp(str[i], "<<") == 0) && !inquote(str[i]) && \
			str[i + 1])
		{
				i += 2;
		}
		else if (((str[i][start] == '<' && str[i][start + 1] == '<') \
			|| (str[i][start] == '>' && str[i][start + 1] == '>') ||
			(str[i][start] == '<' && str[i][start + 1] != '<') \
			|| (str[i][start] == '>' && str[i][start + 1] != '>')) && !inquotes(str[i], start))
		{
			i++;
		}
		else
			i++;
		if (st[0] != '\0')
		{
			done = 1;
			cmd[j++] = trimquotes(st);
			free(st);
		}
		else if (st)
			free(st);
	}
	if (done == 0)
	{
		free(cmd);
		return (NULL);
	}
	cmd[j] = NULL;
	return (cmd);
}

void	checkredirs(char *line, t_all *all)
{
	int			i;
	int			j;
	t_cmdfinal	*new;
	char		**str;
	t_commands	*tmp1;
	t_redirs 	*tmp2;

	j = 0;
	i = 0;
	all->cmd = NULL;
	i = 0;
	str = ft_splitline(line, '|');
	all->redir = NULL;
	all->here = NULL;
	while (str[i] != NULL)
	{
		checkredirsout(&all->redir, str[i]);
		checkredirsin(&all->redir, str[i], all);
		i++;
	}
	freestrpiped(str);
	i = 0;
	if (all->coms->piped == 0)
	{
		new = malloc(sizeof(t_cmdfinal));
		initfinal(new);
		new->parsed = checkcommand(all, all->coms->parsed);
		addbackcmd(&all->cmd, new);
	}
	else
	{
		tmp1 = all->coms;
		tmp2 = all->redir;
		while (all->coms)
		{
			new = malloc(sizeof(t_cmdfinal));
			initfinal(new);
			new->parsedpipe = checkcommand(all, all->coms->parsedpipe);
			addbackcmd(&all->cmd, new);
			all->coms = all->coms->next;
			all->redir = all->redir->next;
			i++;
		}
		all->coms = tmp1;
		all->redir = tmp2;
	}
}