/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmkrtchy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:11:51 by tmkrtchy          #+#    #+#             */
/*   Updated: 2021/02/16 16:12:43 by tmkrtchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *str)
{
	char	*new;
	ssize_t	i;

	new = ft_strnew(ft_strlen(str));
	if (new == NULL)
		return (NULL);
	i = -1;
	while (str[++i])
		new[i] = str[i];
	return (new);
}

char	*ft_strchr(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i] != (char)c)
		if (!s[i++])
			return (NULL);
	return ((char *)&s[i]);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL || !(ptr = (char *)malloc(ft_strlen(s1)
		+ ft_strlen(s2) + 1)))
		return (NULL);
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		ptr[i] = s2[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ptr;

	i = 0;
	if (!s || (long int)len < 0)
		return (NULL);
	ptr = (char *)malloc(len + 1);
	if (ptr == NULL)
		return (NULL);
	while (start < ft_strlen(s) && i < len)
	{
		ptr[i] = s[start];
		i++;
		start++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int		get_next_line(int fd, char **line)
{
	ssize_t		res;
	char		bf[BUFFER_SIZE + (res = 1)];
	static char	*mem = NULL;
	char		*tmp;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	mem == NULL ? mem = ft_strnew(0) : NULL;
	while (!ft_strchr(mem, '\n') && (res = read(fd, bf, BUFFER_SIZE)) > 0)
	{
		bf[res] = '\0';
		tmp = ft_strjoin(mem, bf);
		ft_memdel((void **)&mem);
		mem = tmp;
	}
	if (res == 0)
		*line = ft_strdup(mem);
	else if (res > 0)
		*line = ft_substr(mem, 0, (ft_strchr(mem, '\n') - mem));
	else
		return (-1);
	tmp = ft_strdup(mem + (ft_strlen(*line) + ((res > 0) ? +1 : +0)));
	ft_memdel((void **)&mem);
	mem = tmp;
	return (res == 0 ? 0 * ft_memdel((void **)&mem) : 1);
}
