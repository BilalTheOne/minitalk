/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:30:39 by bel-barb          #+#    #+#             */
/*   Updated: 2023/11/27 14:40:30 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	overflow(long long a, long long b)
{
	long long	result;

	if (a == 0 || b == 0)
		return (0);
	result = a * b;
	if (a == result / b)
		return (0);
	else
		return (1);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	int		i;
	int		j;

	if (overflow(count, size) == 1)
		return (NULL);
	i = (long)count;
	j = (long)size;
	if (i < 0 || j < 0)
		return (NULL);
	ptr = (void *)malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}
