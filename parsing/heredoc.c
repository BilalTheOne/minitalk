/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:29:38 by bel-barb          #+#    #+#             */
/*   Updated: 2024/08/28 10:52:03 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrl_c(int sig)
{
    (void)sig;
    g_signal = 1;
    close(0);
}

void	heredoc(t_env *head, int exp, int fd, char *done, char *s)
{
    char *str;

    while (1)
    {
        s = readline("> ");
        if (!s)
            return ;
        else if (exp == 1)
            str = expand(s, head);
        else
            str = ft_strdup(s);
        if (!ft_strcmp(s, done))
            return (free(s));
        ft_putstr_fd(str, fd);
        ft_putchar_fd('\n', fd);
        free(s);
    }
}

void	heredocu(char *done, int *fd, t_env *head, int exp)
{
    char	*s;
    int     fd2;

    s = NULL;
    fd2 = dup(0);
    if (*fd < 0)
    {
        perror("open");
        return ;
    }
    signal(SIGINT, ctrl_c);
    heredoc(head, exp, *fd, done, s);
    if (g_signal == 1)
    {
        *fd = dup(fd2);
        close(fd2);
        return ;
    }
    close(fd2);
}
