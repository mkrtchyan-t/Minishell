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
		if ((line[i] == '>' && line[i + 1] == '>') || \
			(line[i] == '>' && line[i + 1] != '>'))
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
		if ((line[i] == '<' && line[i + 1] == '<') || \
			(line[i] == '<' && line[i + 1] != '<'))
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

int	checkmalloc(char **str)
{
	int 	i;
	int 	j;

	j = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i][0] == '<' && str[i][1] == '<') \
			|| (str[i][0] == '>' && str[i][1] == '>') ||
			(str[i][0] == '<' && str[i][1] != '<') \
			|| (str[i][0] == '>' && str[i][1] != '>'))
		{
			i += 2;
		}
		else if ((ft_strcmp(str[i], ">") == 0) || (ft_strcmp(str[i], ">>") == 0)\
			|| ft_strcmp(str[i], "<") == 0 || ft_strcmp(str[i], "<<") == 0)
		{
			i++;
		}
		else
		{
			j++;
			i++;
		}
	}
	return (j);
}

char	**checkcommand(t_all *all, char **str)
{
	int 	i;
	char 	**cmd;
	int 	len;
	int 	j;
	int  	done;

	j = 0;
	i = 0;
	done = 0;
	len = checkmalloc(str);
	cmd = malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (str[i])
	{
		if ((ft_strcmp(str[i], ">") == 0) || (ft_strcmp(str[i], ">>") == 0)\
			|| ft_strcmp(str[i], "<") == 0 || ft_strcmp(str[i], "<<") == 0)
		{
			i += 2;
		}
		else if ((str[i][0] == '<' && str[i][1] == '<') \
			|| (str[i][0] == '>' && str[i][1] == '>') ||
			(str[i][0] == '<' && str[i][1] != '<') \
			|| (str[i][0] == '>' && str[i][1] != '>'))
		{
			i++;
		}
		else
		{
			done = 1;
			cmd[j] = ft_strdup(str[i]);
			j++;
			i++;
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
	str = ft_split(line, '|');
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