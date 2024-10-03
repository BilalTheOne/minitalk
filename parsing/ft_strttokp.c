/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strttokp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:17:42 by bel-barb          #+#    #+#             */
/*   Updated: 2024/08/28 10:17:45 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_delimiter(char c, char *delims)
{
	while (*delims)
	{
		if (c == *delims)
			return (1);
		delims++;
	}
	return (0);
}
char *ft_strttok(char *str, char *delims)
{
	static char *last = NULL;
	if (str != NULL)
		last = str;
	if (last == NULL)
		return NULL;
	while (is_delimiter(*last, delims))
		last++;
	if (*last == '\0')
		return NULL;
	char *start = last;
	if (delims[0] == '|')
		return (start);
	while (!is_delimiter(*last, delims) && *last != '\0' && ft_isalnum(*last))
		last++;
	if (*last == '\0')
		last = NULL;
	else
	{
		*last = '\0';
		last++;
	}
	return start;
}