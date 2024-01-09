/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 21:55:06 by bel-barb          #+#    #+#             */
/*   Updated: 2024/01/05 11:14:03 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		lenght;
	char	*returrn;

	if (!s || !f)
		return (NULL);
	lenght = ft_strlen(s);
	i = 0;
	returrn = (char *)malloc(sizeof(char) * lenght + 1);
	if (!returrn)
		return (0);
	while (i < lenght)
	{
		returrn[i] = (*f)(i, s[i]);
		i++;
	}
	returrn[i] = '\0';
	return (returrn);
}
