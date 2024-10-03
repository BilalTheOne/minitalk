/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaida <ohaida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 22:16:48 by ohaida            #+#    #+#             */
/*   Updated: 2024/09/27 14:31:26 by ohaida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*ft_lstlast(t_command *lst)
{
    if (!lst)
        return (lst);
    while (lst->next && lst->pipe == 1)
    {
        lst = lst->next;
    }
    return (lst);
}
