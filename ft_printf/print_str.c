/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 18:04:10 by bel-barb          #+#    #+#             */
/*   Updated: 2023/12/14 19:53:38 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_str(char *str)
{
	int	count;

	count = 0;
	if (str == NULL)
	{
		print_str("(null)");
		return (6);
	}
	while (*str)
	{
		print_char((int)*str);
		count++;
		str++;
	}
	return (count);
}
