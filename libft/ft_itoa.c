/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaida <ohaida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 11:20:13 by ohaida            #+#    #+#             */
/*   Updated: 2023/11/08 10:48:49 by ohaida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	alloc_mem(int n)
{
	int		i;
	long	res;

	i = 0;
	res = n;
	if (res <= 0)
	{
		res = -res;
		i++;
	}
	while (res > 0)
	{
		res = res / 10;
		i++;
	}
	return (i);
}

static int	fill_str(char *str, long n, int index)
{
	if (n < 0)
	{
		str[index] = '-';
		n = -n;
		index++;
	}
	if (n < 10)
	{
		str[index] = n + 48;
	}
	else
	{
		index = fill_str(str, (n / 10), index);
		str[index] = (n % 10) + 48;
	}
	return (index + 1);
}

char	*ft_itoa(int n)
{
	char	*str;

	str = ft_malloc(alloc_mem(n) + 1, 0);
	if (str == NULL)
		return (NULL);
	fill_str(str, (long) n, 0);
	str[alloc_mem(n)] = '\0';
	return (str);
}
