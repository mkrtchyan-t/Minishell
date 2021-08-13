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

void 	checkquotes(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' && !isclosed(&i, line, '\''))
			readline("quote> ");
		else if (line[i] == '\"' && !isclosed(&i, line, '\"'))
			readline("quote> ");
		i++;
	}
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
		trimed[j++] = str[i];
		i++;
	}
	trimed[j] = '\0';
	return (trimed);
}