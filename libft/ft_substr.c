/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:43:58 by bel-barb          #+#    #+#             */
/*   Updated: 2023/11/15 10:53:47 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*returrn;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		returrn = ft_strdup("");
		return (returrn);
	}
	else if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	returrn = (char *)malloc(sizeof(char) * (len + 1));
	if (!returrn)
		return (0);
	while (i < len && s[start] != '\0')
	{
		returrn[i] = s[start];
		i++;
		start++;
	}
	returrn[i] = '\0';
	return (returrn);
}
