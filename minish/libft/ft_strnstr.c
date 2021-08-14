/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arastepa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 14:36:21 by arastepa          #+#    #+#             */
/*   Updated: 2021/01/28 17:19:59 by arastepa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;
	char	*to_find;

	str = (char *)haystack;
	to_find = (char *)needle;
	if (ft_strlen(needle) == 0)
		return (str);
	i = 0;
	while ((int)i <= (int)ft_strlen(str) - (int)ft_strlen(to_find) && i < len)
	{
		j = 0;
		while (j < ft_strlen(to_find) && (i + j) < len)
		{
			if (str[i + j] != to_find[j])
				break ;
			j++;
		}
		if (j == ft_strlen(to_find))
			return (&str[i]);
		i++;
	}
	return (0);
}
