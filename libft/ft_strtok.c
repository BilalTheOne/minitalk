/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaida <ohaida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 01:24:48 by ohaida            #+#    #+#             */
/*   Updated: 2024/09/27 15:11:53 by ohaida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_strtok(char *str, char delim) 
{
    static char *last = NULL;
    if (str != NULL) {
        last = str;
    }
    if (last == NULL) {
        return NULL;
    }
    while (*last == delim) {
        last++;
    }
    if (*last == '\0') {
        return NULL;
    }
    char *start = last;
    while (*last != '\0' && *last != delim) {
        if (*last == '"' || *last == '\'')
        {
            char c = *last;
            last++;
            while (*last != '\0' && *last != c)
                last++;
        }
        if (*last != '\0')
            last++;
    }
    if (*last == '\0') {
        last = NULL;
    } else {
        *last = '\0';
        last++;
    }
    return start;
}
