#include "minishell.h"

int	addback(t_redirs **a, t_redirs *new)
{
	t_redirs *lst;

	lst = last(*a);
	if (lst)
	{
		lst->next = new;
	}
	else
		*a = new;
	return (1);
}

t_redirs *last(t_redirs *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
		{
			return (lst);
		}
		lst = lst->next;
	}
	return (NULL);
}

int	cmd_size(t_cmdfinal *cmd)
{
	t_cmdfinal	*tmp;
	int			i;

	i = 0;
	tmp = cmd;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	cmdline_size(char **cmd)
{
	int i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

char *join(char *f, char c)
{
	char 	*joined;
	int 	i;

	i = 0;
	joined = (char *)malloc(sizeof(char) * (ft_strlen(f) + 2));
	while (f[i] != '\0')
	{
		joined[i] = f[i];
		i++;
	}
	joined[i] = c;
	joined[i + 1] = '\0';
	return(joined);
}
