/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 18:11:44 by bel-barb          #+#    #+#             */
/*   Updated: 2023/12/03 17:38:14 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	digit_number(long n)
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

static char	*ft_itoa(long n)
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

int	print_num(long n)
{
	int		len;
	char	*num;

	len = 0;
	num = ft_itoa(n);
	if (num == NULL)
		return (-1);
	len = print_str(num);
	free(num);
	return (len);
}
