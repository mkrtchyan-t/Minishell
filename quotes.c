#include "minishell.h"

int	isclosed(int *i,  char *line, char c)
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

int	checkquotes(char *line)
{
	int i;
	int t;

	t = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (!t && line[i] == '\'' && !isclosed(&i, line, '\''))
			return (1);
		else if (!t && line[i] == '\"' && !isclosed(&i, line, '\"'))
			return (1);
		else if (line[i] == '\\')
		{
			if (t == 1)
				t = 0;
			else
				t = 1;
			i++;
			if (t == 1)
			{
				if (!line[i + 1])
					return (2);
			}
			continue ;
		}
		else if (line[i] == '|' && !line[i + 1])
			return (3);
		t = 0;
		i++;
	}
	return (0);
}

char	*trimquotes(char *str)
{
	int		i;
	int		j;
	char	*trimed;
	int		t;

	t = 0;
	trimed = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	j = 0;
	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '\"' && !insquotes(str, i))
		{
			if (!t)
				continue ;
		}
		else if (str[i] == '\'' && !indquotes(str, i))
		{
			if (!t)
				continue ;
		}
		else if (!t && (str[i] == '\\' && !insquotes(str, i)) && \
				(str[i + 1] == '\\' || str[i + 1] == '"' || \
				str[i + 1] == '$'))
		{
			t = 1;
			continue ;
		}
		else if (!t && (str[i] == '\\' && !insquotes(str, i) && !indquotes(str, i)) && \
				str[i + 1] == '\'')
		{
			t = 1;
			continue ;
		}
		t = 0;
		trimed[j++] = str[i];
	}
	trimed[j] = '\0';
	return (trimed);
}

int	getsiz(char *str, int start, int end)
{
	int	i;
	int	j;

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

char	*replacequest(char *str, int start, int end, t_all *all)
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

char	*replacestr(char *str, int start, int end, t_all *all)
{
	char	*tmp[3];
	char	*varname;
	char	*path;
	int		i;
	int		j;
	char	*replaced;

	varname = (char *)malloc(sizeof(char) * (getsiz(str, start, end) + 1));
	i = 0;
	j = 0;
	while (str[i])
	{	
		if (i >= start && i <= end)
			varname[j++] = str[i];
		i++;
	}
	varname[j] = '\0';
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

int	insquote(char *str, int index)
{
	int	start;
	int	last;
	int	i;

	i = 0;
	start = 0;
	last = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && !indquotes(str, i))
		{
			start = i;
			i++;
			while (str[i] != '\'')
				i++;
			last = i;
			break ;
		}
		i++;
	}
	if (start != last)
		if (index >= start && index <= last)
			return (1);
	return (0);
}

void	checkdolar(char **str, t_all *all)
{
	int		i;
	char	*tmp;
	int		start;
	int		end;
	int		t;

	t = 0;
	i = 0;
	while ((*str)[i] != '\0')
	{
		if (!t && (*str)[i] == '$' && (!(*str)[i + 1] || (*str)[i + 1] == '/' || (*str)[i + 1] == ' '))
		{
			;
		}
		else if (!t && (*str)[i] == '$' && (*str)[i + 1] != '?' && !insquote(*str, i))
		{
			start = i + 1;
			while ((*str)[i] && (*str)[i] != '\"' && (*str)[i] != '\'' && (*str)[i] != ' ')
				i++;
			end = i - 1;
			if ((*str)[end] == '"' || (*str)[end] == '\'')
				end--;
			tmp = *str;
			*str = replacestr(*str, start, \
							end, all);
			free(tmp);
		}
		else if (!t && (*str)[i] == '$' && (*str)[i + 1] == '?' && !insquote(*str, i))
		{
			start = i + 1;
			end = i + 2;
			tmp = *str;
			*str = replacequest(*str, start, \
							end, all);
			free(tmp);
		}
		else if ((*str)[i] == '\\')
		{
			if (t == 1)
				t = 0;
			else
				t = 1;
			i++;
			continue ;
		}
		t = 0;
		i++;
	}
}
