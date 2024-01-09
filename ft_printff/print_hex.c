/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 20:46:44 by bel-barb          #+#    #+#             */
/*   Updated: 2023/12/02 16:58:01 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	hex_cap(unsigned long n, int *printed, char *hex)
{
	if (n == 0)
	{
		*printed += print_char(hex[0]);
		return ;
	}
	if (n <= 15)
	{
		*printed += print_char(hex[n % 16]);
		return ;
	}
	hex_cap(n / 16, printed, hex);
	*printed += print_char(hex[n % 16]);
}

int	print_hex(unsigned long n, int c)
{
	int	printed;

	printed = 0;
	if (c == 'p')
	{
		printed += print_str("0x");
		hex_cap(n, &printed, "0123456789abcdef");
		return (printed);
	}
	if (c == 'x')
		hex_cap(n, &printed, "0123456789abcdef");
	else
		hex_cap(n, &printed, "0123456789ABCDEF");
	return (printed);
}
