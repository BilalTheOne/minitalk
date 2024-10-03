/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaida <ohaida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 01:25:10 by ohaida            #+#    #+#             */
/*   Updated: 2024/09/25 07:33:57 by ohaida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_strcat(char *dest, char *src) 
{
	int i = 0;
	int j = 0;
	if (dest == NULL || src == NULL) {
		return NULL;
	}
	while (dest[i] != '\0') {
		i++;
	}
	while (src[j] != '\0') {
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return dest;
}

char *ft_strcpy(char *dest, char *src) 
{
	int i = 0;
	while (src[i] != '\0') {
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return dest;
}
