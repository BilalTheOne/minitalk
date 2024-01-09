/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 22:15:39 by bel-barb          #+#    #+#             */
/*   Updated: 2023/11/24 13:47:44 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digit_number(int n)
{
	int	digits;

	digits = 0;
	if (n < 0)
	{
		n = -n;
		digits++;
	}
	if (n == 0)
		return (1);
	while (n)
	{
		n = n / 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	int		digits;
	char	*result;
	int		neg;

	digits = digit_number(n);
	neg = 0;
	result = (char *)malloc(sizeof(char) * digits + 1);
	if (!result)
		return (NULL);
	result[digits] = '\0';
	if (n < 0)
		neg = 1;
	while (digits > 0)
	{
		if (n < 0)
			result[digits - 1] = ((n % 10) * -1) + '0';
		else
			result[digits - 1] = (n % 10) + '0';
		n /= 10;
		digits--;
	}
	if (neg == 1)
		result[0] = '-';
	return (result);
}
