/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:45:35 by bel-barb          #+#    #+#             */
/*   Updated: 2023/11/11 00:38:33 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;
	char	*returrn;

	if (s1 == NULL)
		return (NULL);
	i = 0;
	j = ft_strlen(s1) - 1;
	k = 0;
	if (!set)
		return (ft_strdup(s1));
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (j >= 0 && ft_strchr(set, s1[j]))
		j--;
	if (i > j)
		return (ft_strdup(""));
	returrn = (char *)malloc(sizeof(char) * (j - i + 2));
	if (!returrn)
		return (NULL);
	while (i <= j)
		returrn[k++] = s1[i++];
	returrn[k] = '\0';
	return (returrn);
}
