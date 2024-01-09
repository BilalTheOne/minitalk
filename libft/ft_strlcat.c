/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 05:43:59 by bel-barb          #+#    #+#             */
/*   Updated: 2023/11/28 12:50:08 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	d;
	size_t	s;

	i = 0;
	j = 0;
	s = 0;
	if (dst != NULL)
		while (dst[j])
			j++;
	d = j;
	while (src[s])
		s++;
	if (dstsize > d)
		d = d + s;
	else
		d = dstsize + s;
	if (!dstsize)
		return (d);
	while (src[i] && j < dstsize - 1)
		dst[j++] = src[i++];
	dst[j] = '\0';
	return (d);
}
