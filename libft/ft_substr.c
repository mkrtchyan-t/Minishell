/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arastepa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 18:21:38 by arastepa          #+#    #+#             */
/*   Updated: 2021/01/29 19:13:57 by arastepa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;

	if (!(dest = (char *)malloc(sizeof(char) * (len + 1))))
	{
		return (NULL);
	}
	i = start;
	if (ft_strlen(s) > start)
	{
		while (i < start + len)
		{
			dest[i - start] = s[i];
			i++;
		}
	}
	dest[i - start] = '\0';
	return (dest);
}
