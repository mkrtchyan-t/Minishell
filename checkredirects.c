#include "minishell.h"

int 	ft_isspace(char c)
{
	return (c == '\t' || c== '\n' || c== '\v' || c== '\f' \
			|| c== '\r' || c == ' ');
}

void 	checkredirsout(t_redirs **redir, char *line)
{
	int 		i;
	t_redirs 	*new;
	int  		type;
	char 		*tmp;

	new = NULL;
	i = 0;
	while (line[i] != '\0')
	{
		type = ((line[i] == '>' && line[i + 1] == '>') ? 2: 0);
		if (((line[i] == '>' && line[i + 1] == '>') || \
			(line[i] == '>' && line[i + 1] != '>')) && !inquotes(line, i))
		{
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
}

void 	checkredirsin(t_redirs **redir, char *line)
{
	int 		i;
	t_redirs 	*new;
	t_redirs  	*tmp;
	int  		type;
	char 		*tmp2;

	new = NULL;
	i = 0;
	while (line[i] != '\0')
	{	
		type = (line[i] == '<' && line[i + 1] == '<') ? 2: 0;
		if (((line[i] == '<' && line[i + 1] == '<') || \
			(line[i] == '<' && line[i + 1] != '<')) && !inquotes(line, i))
		{
			new = (t_redirs *)malloc(sizeof(t_redirs));
			initredirs(new);
			new->redir = 1;
			new->filein = ft_strdup("");
			new->typefilein = (type == 2) ? 2: 1;
			while (line[i] == '<' && line[i])
				i++;
			while (ft_isspace(line[i]) && line[i])
				i++;
			while (!ft_isspace(line[i]) && line[i] != '<' && line[i] != '>' && line[i])
			{
				tmp2 = new->filein;
				new->filein = join(new->filein, line[i]);
				free(tmp2);
				i++;
			}
			i--;
		}
		i++;
	}
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
}

static 	int inquote(char *str)
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
	int 	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static  int checksingle(char **str, t_all *all, int start, int i)
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
	int 	i;
	char 	**cmd;
	int 	j;
	int  	done;
	int  	start;
	char  	*st;
	int  	l;

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
			free(cmd);
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
		return (NULL);
	cmd[j] = NULL;
	return (cmd);
}

void 	checkredirs(char *line, t_all *all)
{
	int 	 	i;
	t_cmdfinal 	*new;
	char 		**str;
	t_commands	*tmp;

	i = 0;
	all->cmd = NULL;
	i = 0;
	str = ft_splitline(line, '|');
	all->redir = NULL;
	while (str[i] != NULL)
	{	
		checkredirsout(&all->redir, str[i]);
		checkredirsin(&all->redir, str[i]);
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
		tmp = all->coms;
		while (all->coms)
		{
			new = malloc(sizeof(t_cmdfinal));
			initfinal(new);
			new->parsedpipe = checkcommand(all, all->coms->parsedpipe);
			addbackcmd(&all->cmd, new);
			all->coms = all->coms->next;
			i++;
		}
		all->coms = tmp;
	}
}