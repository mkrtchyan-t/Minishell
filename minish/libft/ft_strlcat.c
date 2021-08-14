/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arastepa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:24:53 by arastepa          #+#    #+#             */
/*   Updated: 2021/01/27 17:28:04 by arastepa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	int		len;
	int		j;

	i = 0;
	while (dst[i] != '\0' && i < dstsize)
	{
		i++;
	}
	if (i == dstsize)
		return (ft_strlen(src) + i);
	len = dstsize - i;
	j = 0;
	while (j < (len - 1) && src[j] != '\0')
	{
		dst[j + i] = src[j];
		j++;
	}
	dst[j + i] = '\0';
	return (i + ft_strlen(src));
}
