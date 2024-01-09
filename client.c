/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:08:11 by bel-barb          #+#    #+#             */
/*   Updated: 2024/01/09 15:11:34 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/libft.h"
#include "ft_printf/ft_printf.h"

char	*char_to_binary(unsigned char c)
{
	int		i = 7;
	int		j = 0;
	char *str = malloc(10);
	while(i >= 0) {
		if (c & (1 << i))
			str[j] = '1';
		else 
			str[j] = '0';
		i--;
		j++;
	}
	str[8] = ' ';
	return (str);
}
char    *str_to_binary(char *str)
{
	int		i = 0;
	int		j = 0;
	char	*result;
	while (str[i] != '\0')
		i++;
	result = malloc((i * 8) + i);
	while (i > 0)
	{
		result = ft_strjoin(result, char_to_binary(str[j]));
		i--;
		j++;
	}
	return(result);
}
#include <stdio.h>
#include <signal.h>
int main()
{
	// char	*str2 = str_to_binary("aaaa");
	int i;
	scanf("%d", &i);
	printf("id : %d", i);
	kill(i, SIGINT);
	return 0;
}