/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:51:49 by bel-barb          #+#    #+#             */
/*   Updated: 2024/03/30 00:40:23 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	bin_to_send(char c, int pid)   
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (c & (1 << i))
		{
			if (kill(pid, SIGUSR1) == -1)
				return (-1);
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				return (-1);
		}
		i--;
		usleep(500);
	}
	return (0);
}

int	str_to_char(char *str, int pid)
{
	int	i;
	int	j;

	i = ft_strlen(str);
	j = 0;
	while (i > 0)
	{
		if (bin_to_send(str[j], pid) == -1)
			return (-1);
		i--;
		j++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	if (argc != 3)
	{
		ft_printf("Invalid input. try this format: ./client 99999 'text'");
		return (0);
	}
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[1]) > 99999)
	{
		ft_printf("INVALID PID (0 < pid < 99999)");
		return (0);
	}
	if (argc == 3)
	{
		if (str_to_char(argv[2], ft_atoi(argv[1])) == -1)
		{
			ft_printf("KILL ERROR (check pid validity)");
			return (0);
		}
	}
	return (0);
}
