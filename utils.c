#include "minishell.h"

int	addback(t_redirs **a, t_redirs *new)
{
	t_redirs *lst;

	lst = last(*a);
	if (lst)
		lst->next = new;
	else
		*a = new;
	return (1);
}

t_redirs *last(t_redirs *lst)
{
	while (lst)
	{
		if (!lst->next)
		{
			return (lst);
		}
		lst = lst->next;
	}
	return (NULL);
}
