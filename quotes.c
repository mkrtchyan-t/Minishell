#include "minishell.h"

int 	isclosed(int *i,  char *line, char c)
{
	(*i)++;
	while (line[*i] != c && line[*i] != '\0')
	{
		(*i)++;
	}
	if (line[*i] == '\0')
		return (0);
	return (1);
}

int 	checkquotes(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' && !isclosed(&i, line, '\''))
			return (0);
		else if (line[i] == '\"' && !isclosed(&i, line, '\"'))
			return (0);
		else if (line[i] == '\\')
			break ;
		i++;
	}
	return (1);
}

char 	*trimquotes(char *str)
{
	int 	i;
	int 	j;
	char 	*trimed;

	trimed = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	j = 0;
	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '\"')
			continue ;
		else if (str[i] == '\'')
			continue ;
		else if ((str[i] == '\\' && !insquotes(str, i)) &&\
				 (str[i + 1] == '\\' || str[i + 1] == '"' ||\
				  str[i + 1] == '$'))
			continue ;
		else if ((str[i] == '\\' && !insquotes(str, i) && !indquotes(str, i)) &&\
				 str[i + 1] == '\'')
			continue ;
		trimed[j++] = str[i];
	}
	trimed[j] = '\0';
	return (trimed);
}

int getsiz(char *str, int start, int end)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (i >= start && i <= end)
		{
			j++;
		}
		i++;
	}
	return (j);
}

char *replacequest(char *str, int start, int end, t_all *all)
{
	char *tmp[3];
	char *tmp2;
	char *varname;
	char *replaced;

	varname = ft_itoa(all->return_val);
	tmp[0] = ft_substr(str, 0, start - 1);
	tmp[1] = ft_substr(str, end, ft_strlen(str));
	tmp[2] = ft_strjoin(tmp[0], varname);
	replaced = ft_strjoin(tmp[2], tmp[1]);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	free(varname);
	return (replaced);
}

char *replacestr(char *str, int start, int end, t_all *all)
{
	char *tmp[3];
	char *varname;
	char *path;
	int i;
	int j;
	char *replaced;

	varname = (char *)malloc(sizeof(char) * (getsiz(str, start, end) + 1));
	i = 0;
	j = 0;
	while (str[i])
	{	
		if (i >= start && i <= end)
			varname[j++] = str[i];
		i++;
	}
	tmp[0] = ft_substr(str, 0, start - 1);
	tmp[1] = ft_substr(str, end + 1, ft_strlen(str));
	path = ft_getenv(all->envp, varname);
	if (path)
		tmp[2] = ft_strjoin(tmp[0], path);
	if (path != NULL)
		replaced = ft_strjoin(tmp[2], tmp[1]);
	else
		replaced = ft_strjoin(tmp[0], tmp[1]);
	if (path)
		free(path);
	free(tmp[0]);
	free(tmp[1]);
	if (path)
		free(tmp[2]);
	free(varname);
	return (replaced);
}

void checkdolar(char **str, t_all *all)
{
	int i;
	int j;
	char *tmp;
	int start;
	int end;

	i = 0;
	while (str[i] != NULL)
	{
		j = 0;
		while (str[i][j] != '\0')
		{
			if (str[i][j] == '$' && (!str[i][j + 1] || str[i][j + 1] == '\\' || str[i][j + 1] == '/'))
			{
				if (str[i][j + 1] == '\\')
				{
					tmp = str[i];
					str[i] = ft_strdup("$");
					free(tmp);
				}
			}
			else if (str[i][j] == '$' && str[i][j + 1] != '?' && !insquotes(str[i], j))
			{
				start = j + 1;
				while (str[i][j] && str[i][j] != ' ')
					j++;
				end = j - 1;
				if (str[i][end] == '"')
					end--;
				tmp = str[i];
				str[i] = replacestr(str[i], start, \
							end, all);
				free(tmp);
			}
			else if (str[i][j] == '$' && str[i][j + 1] == '?' && !insquotes(str[i], j))
			{
				start = j + 1;
				end = j + 2;
				tmp = str[i];
				str[i] = replacequest(str[i], start, \
							end, all);
				free(tmp);
			}
			else if (str[i][j] == '\\')
				break ;
			j++;
		}
		i++;
	}
}