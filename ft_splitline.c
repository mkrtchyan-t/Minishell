#include "minishell.h"

int	indquotes(char const *str, int index)
{
	int start;
	int last;
	int i;

	i = 0;
	start = 0;
	last = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
		{
			start = i;
			i++;
			while (str[i] != '\"')
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

int	insquotes(char const *str, int index)
{
	int start;
	int last;
	int i;

	i = 0;
	start = 0;
	last = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
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

int	inquotes(char const *str, int index)
{
	int start;
	int last;
	int i;

	i = 0;
	start = 0;
	last = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			start = i;
			i++;
			while (str[i] != str[start])
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

static int	count_words(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		while (str[i] && (str[i] != c || (str[i] == c && inquotes(str, i))))
		{
			count++;
			while (str[i] && ((str[i] != c || (str[i] == c && inquotes(str, i)))))
				i++;
		}
	}
	return (count);
}

static char	*malloc_tmp(char const *s, char c)
{
	char	*tmp;
	int		i;

	i = 0;
	while (s[i] && (s[i] != c || inquotes(s, i)))
		i++;
	if (!(tmp = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (s[i] && (s[i] != c || inquotes(s, i)))
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	**ft_splitline(char const *s, char c)
{
	char	**arr;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	if (!(arr = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && (s[i] != c || inquotes(s, i)))
		{
			arr[j++] = malloc_tmp(s + i, c);
			while (s[i] && (s[i] != c || inquotes(s, i)))
				i++;
		}
	}
	arr[j] = NULL;
	return (arr);
}