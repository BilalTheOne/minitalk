/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaida <ohaida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:21:40 by ohaida            #+#    #+#             */
/*   Updated: 2024/09/21 11:12:10 by ohaida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_space(char c)
{
	if (c == '\f' || c == '\n' || c == ' ')
		return (1);
	if (c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

static const char	*is_oper(char c, const char **str, int *neg)
{
	if (c == '+' || c == '-')
	{
		if (c == '-')
			*neg = (*neg) * -1;
		return ((*str) + 1);
	}
	return (*str);
}

__int128	ft_atoi(const char *str)
{
	__int128			n;
	int					neg;

	n = 0;
	neg = 1;
	while (is_space(*str))
		str++;
	str = is_oper(*str, &str, &neg);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (n * neg);
		n = n * 10 + (*str) - '0';
		str++;
	}
	return (n * neg);
}
