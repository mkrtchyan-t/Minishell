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

int  	space(char *str)
{
	int 	i;
	int 	j;
	char 	*trimed;

	j = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"')
			{
				i++;
				j++;
			}
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
			{
				i++;
				j++;
			}
		}
			else if ((str[i] == '\\' && !insquotes(str, i)) &&\
				 (str[i + 1] == '\\' || str[i + 1] == '"' ||\
				  str[i + 1] == '$'))
		{
			i++;
		}
		else if ((str[i] == '\\' && !insquotes(str, i) && !indquotes(str, i)) &&\
				 str[i + 1] == '\'')
		{
			i++;
		}
		j++;
		i++;
	}
	return (j);
}

char 	*trimquotes(char *str)
{
	int 	i;
	int 	j;
	char 	*trimed;
	int 	size;

	size = space(str);
	trimed = (char *)malloc(sizeof(char) * (size + 1));
	j = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"')
			{
				trimed[j++] = str[i];
				i++;
			}
			i++;
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
			{
				trimed[j++] = str[i];
				i++;
			}
			i++;
		}
		else if ((str[i] == '\\' && !insquotes(str, i)) &&\
				 (str[i + 1] == '\\' || str[i + 1] == '"' ||\
				  str[i + 1] == '$'))
		{
			i++;
		}
		else if ((str[i] == '\\' && !insquotes(str, i) && !indquotes(str, i)) &&\
				 str[i + 1] == '\'')
		{
			i++;
		}
		trimed[j++] = str[i];
		i++;
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
	char *tmp1;
	char *tmp2;
	char *varname;
	int i;
	int j;
	char *replaced;

	varname = ft_strdup(ft_itoa(all->return_val));
	tmp1 = ft_substr(str, 0, start - 1);
	tmp2 = ft_substr(str, end, ft_strlen(str));
	replaced = ft_strjoin(ft_strjoin(tmp1, varname), tmp2);
	free(tmp1);
	free(tmp2);
	return (replaced);
}

char *replacestr(char *str, int start, int end, t_all *all)
{
	char *tmp1;
	char *tmp2;
	char *varname;
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
	tmp1 = ft_substr(str, 0, start - 1);
	tmp2 = ft_substr(str, end + 1, ft_strlen(str));
	if (ft_getenv(all->envp, varname) != NULL)
		replaced = ft_strjoin(ft_strjoin(tmp1, ft_getenv(all->envp, varname)), tmp2);
	else
		replaced = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
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
			if (str[i][j] == '$' && str[i][j + 1] != '?' && !insquotes(str[i], j))
			{
				start = j + 1;
				while (str[i][j] && str[i][j] != ' ')
					j++;
				end = j - 1;
				if (str[i][end] == '"')
					end--;
				tmp = str[i];
				str[i] = ft_strdup(replacestr(str[i], start, \
							end, all));
				free(tmp);
			}
			else if (str[i][j] == '$' && str[i][j + 1] == '?' && !insquotes(str[i], j))
			{
				start = j + 1;
				end = j + 2;
				tmp = str[i];
				str[i] = ft_strdup(replacequest(str[i], start, \
							end, all));
				free(tmp);
			}
			else if (str[i][j] == '\\')
				break ;
			j++;
		}
		i++;
	}
}