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