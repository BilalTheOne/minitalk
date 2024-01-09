/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 02:11:27 by bel-barb          #+#    #+#             */
/*   Updated: 2023/11/14 22:15:28 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*sp_neg(char *str, int *neg)
{
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
	{
		*neg = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	return (str);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;
	long	max;
	char	*st;

	i = 0;
	sign = 1;
	result = 0;
	max = 0;
	st = sp_neg((char *)str, &sign);
	while (st[i] >= '0' && st[i] <= '9')
	{
		result = result * 10 + (st[i] - '0');
		if (result < max && sign == -1)
			return (0);
		if (result < max && sign == 1)
			return (-1);
		i++;
		max = result;
	}
	return ((int)result * sign);
}
