/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaida <ohaida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:58:41 by ohaida            #+#    #+#             */
/*   Updated: 2024/09/30 15:29:01 by ohaida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_list *all_fds = NULL;

static void	close_all(void)
{
    t_list	*tmp;

    while (all_fds)
    {
        close(*(int*)all_fds->content);
        tmp = all_fds;
        all_fds = all_fds->next;
        free(tmp->content);
        free(tmp);
    }
}

static void	add_fd(int fd)
{
    t_list *new_node = malloc(sizeof(t_list));
    if (!new_node)
    {
        ft_putstr_fd("Error\n", 2);
        exit(1);
    }
    int *fd_ptr = malloc(sizeof(int));
    *fd_ptr = fd;
    new_node->content = fd_ptr;
    new_node->next = all_fds;
    all_fds = new_node;
}

int	open_with_gc(const char *pathname, int flags, int per, int true_v1)
{
    int fd;
    
    if (true_v1 == 0)
        fd = open(pathname, flags);
    else
        fd = open(pathname, flags, per);
    if (fd != -1)
        add_fd(fd);
    return (fd);
}

int	pipe_with_gc(int pipefd[2])
{
    int result = pipe(pipefd);
    if (result != -1)
    {
        add_fd(pipefd[0]);
        add_fd(pipefd[1]);
    }
    return result;
}

void	*ft_fds()
{
    close_all();
    return (NULL);
}
