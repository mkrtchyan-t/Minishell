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
	new = malloc(sizeof(t_redirs));
	i = 0;
	j = 0;
	while (ft_strchr((line + i), '>'))
	{
		initredirs(new);
		new->outfile = ft_strdup("");
		j = 0;
		while (line[i] != '\0')
		{
			if ((line[i] == '>' && line[i + 1] == '>') || \
				(line[i] == '>' && line[i + 1] != '>'))
			{
				new->redir = 1;
				while (line[i] == '>' && line[i])
					i++;
				while (ft_isspace(line[i]) && line[i])
					i++;
				while (!ft_isspace(line[i]) && line[i] != '>' && line[i])
				{
					new->outfile[j++] = line[i];
					i++;
				}
			}
			i++;
		}
		if (ft_strcmp(new->outfile, "") != 0)
		{
			addback(&redir, new);
			printf("%s", redir->outfile);
		}
		new = malloc(sizeof(t_redirs));
	}
	printf("%s", redir->next->outfile);
}