/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 22:24:11 by bel-barb          #+#    #+#             */
/*   Updated: 2023/11/03 20:00:55 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	_c;

	_c = (char)c;
	i = 0;
	while (s[i] != '\0' || (_c == '\0' && s[i] == '\0'))
	{
		if (s[i] == _c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}
