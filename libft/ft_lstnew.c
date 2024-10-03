/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:59:26 by bel-barb          #+#    #+#             */
/*   Updated: 2024/08/13 11:26:42 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = ft_malloc(sizeof(t_list), 0);
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	new->next = NULL;
	return (new);
}
