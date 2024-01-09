/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:08:07 by bel-barb          #+#    #+#             */
/*   Updated: 2024/01/09 13:32:08 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_percent(void)
{
	write(1, "%", 1);
	return (1);
}

static int	print_format(char spec, va_list ap)
{
	int	count;

	count = 0;
	if (spec == 'c')
		count += print_char(va_arg(ap, int));
	else if (spec == 's')
		count += print_str(va_arg(ap, char *));
	else if (spec == 'd' || spec == 'i')
		count += print_num((long)(va_arg(ap, int)));
	else if (spec == 'u')
		count += print_num((unsigned int)(va_arg(ap, int)));
	else if (spec == 'x' || spec == 'X')
		count += print_hex((unsigned long)(va_arg(ap, unsigned int)), spec);
	else if (spec == 'p')
		count += print_hex((unsigned long)(va_arg(ap, unsigned long)), spec);
	else if (spec == '%')
		count += print_percent();
	else
		count += write(1, &spec, 1);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;
	int		add;

	if (write(1, "0", 0))
		return (-1);
	va_start(ap, format);
	count = 0;
	while (*format != 0)
	{
		if (*format == '%')
		{
			add = print_format(*(++format), ap);
			if (add < 0)
				return (-1);
			count += add;
		}
		else
			count += write(1, format, 1);
		format++;
	}
	va_end(ap);
	return (count);
}
