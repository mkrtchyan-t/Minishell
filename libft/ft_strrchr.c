/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strrchr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arastepa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 19:14:58 by arastepa          #+#    #+#             */
/*   Updated: 2021/01/24 18:27:01 by arastepa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*dst;
	char	*str;

	str = (char *)s;
	i = 0;
	dst = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			dst = str + i;
		}
		i++;
	}
	if (str[i] == c)
	{
		dst = str + i;
	}
	return (dst);
}
