#include "minishell.h"

int 	ft_isspace(char c)
{
	return (c == '\t' || c== '\n' || c== '\v' || c== '\f' \
			|| c== '\r' || c == ' ');
}

void 	checkredirsout(t_redirs **redir, char *line)
{
	int 		i;
	int 		j;
	t_redirs 	*new;
	int  		type;

	new = NULL;
	j = 0;
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
			j = 0;
			while (!ft_isspace(line[i]) && line[i] != '>' && line[i] != '<' && line[i])
			{
				new->fileout[j++] = line[i];
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
	}
}

void 	checkredirsin(t_redirs **redir, char *line)
{
	int 		i;
	int 		j;
	t_redirs 	*new;
	t_redirs  	*tmp;
	int  		type;

	new = NULL;
	j = 0;
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
			j = 0;
			while (!ft_isspace(line[i]) && line[i] != '<' && line[i] != '>' && line[i])
			{
				new->filein[j++] = line[i];
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

char	**checkcommand(t_all *all, char **str)
{
	int 	i;
	char 	**cmd;
	int 	len;
	int 	j;
	int  	done;
	int  	start;
	char  	*st;

	j = 0;
	i = 0;
	done = 0;
	start = 0;
	len = checkmalloc(str, all);
	cmd = malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (str[i])
	{
		start = 0;
		st = ft_strdup("");
		while (str[i][start] && (str[i][start] != '>' && str[i][start] != '<'))
		{
			st[start] = str[i][start];
			start++;
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
		}
	}
	cmd[j] = NULL;
	if (done == 0)
		return (NULL);
	return (cmd);
}

void 	checkredirs(char *line, t_all *all)
{
	int 	 	i;
	t_cmdfinal *new;
	char 		**str;

	i = 0;
	all->cmd = NULL;
	new = malloc(sizeof(t_cmdfinal));
	initfinal(new);
	i = 0;
	str = ft_splitline(line, '|');
	all->redir = NULL;
	while (str[i] != NULL)
	{	
		checkredirsout(&all->redir, str[i]);
		checkredirsin(&all->redir, str[i]);
		i++;
	}
	i = 0;
	if (all->coms->piped == 0)
	{
		new->parsed = checkcommand(all, all->coms->parsed);
		all->cmd = new;
	}
	else
	{
		while (all->coms)
		{
			new->parsedpipe = checkcommand(all, all->coms->parsedpipe);
			addbackcmd(&all->cmd, new);
			new = malloc(sizeof(t_cmdfinal));
			initfinal(new);
			all->coms = all->coms->next;
			i++;
		}
	}
}