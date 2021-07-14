#include "minishell.h"

int 	ft_isspace(char c)
{
	return (c == '\t' || c== '\n' || c== '\v' || c== '\f' \
			|| c== '\r' || c == ' ');
}

void 	checkredirs(t_redirs *redir, char *line)
{
	int 		i;
	int 		j;
	t_redirs 	*new;

	redir = NULL;
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
			new->redir = 1;
			new->outfile = ft_strdup("");
			while (line[i] == '>' && line[i])
				i++;
			while (ft_isspace(line[i]) && line[i])
				i++;
			while (!ft_isspace(line[i]) && line[i] != '>' && line[i])
			{
				new->outfile[j++] = line[i];
				i++;
			}
			i--;
		}
		if (new)
		{
			if (ft_strcmp(new->outfile, "") != 0)
				addback(&redir, new);
		}
		new = NULL;
		i++;
	}
}