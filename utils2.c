#include "minishell.h"

t_commands	*lastcom(t_commands *lst)
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

int	addbackcom(t_commands **a, t_commands *new)
{
	t_commands	*lst;

	lst = lastcom(*a);
	if (lst)
	{
		lst->next = new;
	}
	else
		*a = new;
	return (1);
}

t_cmdfinal	*lastcmd(t_cmdfinal *lst)
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

int	addbackcmd(t_cmdfinal **a, t_cmdfinal *new)
{
	t_cmdfinal	*lst;

	lst = lastcmd(*a);
	if (lst)
	{
		lst->next = new;
	}
	else
		*a = new;
	return (1);
}