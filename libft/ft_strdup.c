/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:19:11 by ohaida            #+#    #+#             */
/*   Updated: 2024/09/30 17:29:41 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_strdup(char *s1)
{
    char *s2;

    if (!s1)
        return (NULL);
    s2 = (char *)ft_malloc((ft_strlen(s1) + 1) * sizeof(char), 0);
    if (s2 == NULL)
        return (NULL);
    ft_strcpy(s2, s1);
    return (s2);
}
