/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:08:11 by bel-barb          #+#    #+#             */
/*   Updated: 2024/03/30 00:40:31 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_sigusr(int signum, siginfo_t *info, void *ucontext)  
{
	static pid_t	pid_c;
	static char		x;
	static int		i;

	(void)ucontext;
	if (pid_c != info->si_pid)
	{
		i = 0;
		x = 0;
		pid_c = info->si_pid;
	}
	if (signum == SIGUSR1)
		x = (x << 1) | 1;
	else
		x = (x << 1);
	i++;
	if (i == 8)
	{
		write(1, &x, 1);
		x = 0;
		i = 0;
	}
}

int	main(int argc, char **argv)
{
	int					i;
	struct sigaction	sa;

	sa.sa_sigaction = handle_sigusr;
	sa.sa_flags = SA_SIGINFO;
	ft_printf("my pid is %d\n", getpid());
	(void)argc;
	(void)argv;
	while (1)
	{
		i = 7;
		sigaction(SIGUSR1, &sa, 0);
		sigaction(SIGUSR2, &sa, 0);
		while (i >= 0)
		{
			pause();
			i--;
		}
	}
}
