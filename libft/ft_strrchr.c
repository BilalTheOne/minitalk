/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 23:02:38 by bel-barb          #+#    #+#             */
/*   Updated: 2023/11/06 16:50:31 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	_c;

	len = ft_strlen(s);
	_c = (char)c;
	while (len >= 0)
	{
		if (s[len] == _c)
			return ((char *)&s[len]);
		len--;
	}
	return (0);
}
