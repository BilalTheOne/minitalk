/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 01:24:28 by ohaida            #+#    #+#             */
/*   Updated: 2024/10/02 13:52:27 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_strcmp(const char *s1, const char *s2)
{
    if (s1 == NULL || s2 == NULL) {
        if (s1 == NULL && s2 == NULL) {
            return 0;
        } else if (s1 == NULL) {
            return -1;
        } else {
            return 1;
        }
    }
    while (*s1 && *s2 && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    return (*(unsigned char *)s1 - *(unsigned char *)s2);
}