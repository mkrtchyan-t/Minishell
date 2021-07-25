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

	*redir = NULL;
	new = NULL;
	j = 0;
	i = 0;
	while (line[i] != '\0')
	{	
		j = 0;
		if ((line[i] == '>' && line[i + 1] == '>') || \
			(line[i] == '>' && line[i + 1] != '>'))
		{
			new = malloc(sizeof(t_redirs));
			initredirs(new);
			new->type = 2;
			new->redir = 1;
			new->file = ft_strdup("");
			while (line[i] == '>' && line[i])
				i++;
			while (ft_isspace(line[i]) && line[i])
				i++;
			while (!ft_isspace(line[i]) && line[i] != '>' && line[i] != '<' && line[i])
			{
				new->file[j++] = line[i];
				i++;
			}
			i--;
		}
		if (new)
		{
			if (ft_strcmp(new->file, "") != 0)
				addback(redir, new);
		}
		new = NULL;
		i++;
	}
}

void 	checkredirsin(t_redirs **redir, char *line)
{
	int 		i;
	int 		j;
	t_redirs 	*new;

	new = NULL;
	j = 0;
	i = 0;
	while (line[i] != '\0')
	{	
		j = 0;
		if ((line[i] == '<' && line[i + 1] == '<') || \
			(line[i] == '<' && line[i + 1] != '<'))
		{
			new = malloc(sizeof(t_redirs));
			initredirs(new);
			new->type = 1;
			new->redir = 1;
			new->file = ft_strdup("");
			while (line[i] == '<' && line[i])
				i++;
			while (ft_isspace(line[i]) && line[i])
				i++;
			while (!ft_isspace(line[i]) && line[i] != '<' && line[i] != '>' && line[i])
			{
				new->file[j++] = line[i];
				i++;
			}
			i--;
		}
		if (new)
		{
			if (ft_strcmp(new->file, "") != 0)
				addback(redir, new);
		}
		new = NULL;
		i++;
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
			i++;
		}
		else if ((ft_strcmp(str[i], ">") == 0) || (ft_strcmp(str[i], ">>") == 0)\
			|| ft_strcmp(str[i], "<") == 0 || ft_strcmp(str[i], "<<") == 0)
		{
			i += 2;
		}
		else
		{
			j++;
			i++;
		}
	}
	return (j);
}

char	**checkcommand(char **str)
{
	int 	i;
	char 	**cmd;
	int 	len;
	int 	j;

	j = 0;
	i = 0;
	len = checkmalloc(str);
	cmd = malloc(sizeof(char *) * (len + 1));
	while (str[i])
	{
		if ((ft_strcmp(str[i], ">") == 0) || (ft_strcmp(str[i], ">>") == 0)\
			|| ft_strcmp(str[i], "<") == 0 || ft_strcmp(str[i], "<<") == 0)
		{
			i+=2;
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
			cmd[j] = ft_strdup(str[i]);
			j++;
			i++;
		}
	}
	cmd[j] = NULL;
	return (cmd);
}

void 	checkredirs(char *line, t_all *all)
{
	t_redirs 	redir;
	int 	 	i;
	t_cmdfinal *new;

	i = 0;
	all->cmd = NULL;
	new = malloc(sizeof(t_cmdfinal));
	initfinal(new);
	all->redir = &redir;
	checkredirsout(&all->redir, line);
	checkredirsin(&all->redir, line);
	if (all->coms->piped == 0)
	{
		new->parsed = checkcommand(all->coms->parsed);
		all->cmd = new;
	}
	else
	{
		while (all->coms)
		{
			new->parsedpipe = checkcommand(all->coms->parsedpipe);
			addbackcmd(&all->cmd, new);
			new = malloc(sizeof(t_cmdfinal));
			initfinal(new);
			all->coms = all->coms->next;
			i++;
		}
	}
	// while(all->redir)
	// {
	// 	printf("%d: %s\n", all->redir->type, all->redir->file);
	// 	all->redir = all->redir->next;
	// }
}