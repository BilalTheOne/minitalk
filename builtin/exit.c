/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaida <ohaida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:45:27 by ohaida            #+#    #+#             */
/*   Updated: 2024/09/28 16:32:15 by ohaida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int overflow(__int128 n)
{
	if (n > LLONG_MAX || n < LLONG_MIN)
        return (1);
	return (0);
}

int		max_long(char *s)
{
	if (overflow(ft_atoi(s)) == 1)
		return (0);
	return (1);
}

char	*remove_whitespaces(char *s)
{
	int i = 0;
	int j = 0;
	char *new_s = (char *)ft_malloc(ft_strlen(s) + 1, 0);
	if (!new_s)
		return (NULL);
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t')
			new_s[j++] = s[i];
		i++;
	}
	new_s[j] = '\0';
	return (new_s);
}

void    check_first_arg(char *s)
{
	int i = 0;
	s = remove_whitespaces(s);
	while (s[i])
	{
		if (s[i] == '-' || s[i] == '+')
			i++;	
		if (ft_isdigit(s[i]) == 0 || max_long(s) == 0)
		{
			ft_putstr_fd("exit\n", 1);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(s, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
		i++;
	}
}

void    exit_bult(t_command *cmd, t_env **head, int n)
{
	unsigned char status;

	(void)head;
	if (cmd->args2[1])
	{
		check_first_arg(cmd->args2[1]);
		if (cmd->args2[1] && cmd->args2[2])
		{
			ft_putstr_fd("exit\n", 1);
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			*((unsigned char *)exit_status()) = 1;
			return ;
		}
	}
	if (cmd->args2[1])
		status = (unsigned char)ft_atoi(cmd->args2[1]);
	else
		status = *((unsigned char *)exit_status());
    if (n == 0)
    {
        ft_putstr_fd("exit\n", 1);
        exit(status);
    }   
    else
		exit(status);
}
