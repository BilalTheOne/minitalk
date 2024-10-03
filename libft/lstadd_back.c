/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstadd_back.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:26:30 by bel-barb          #+#    #+#             */
/*   Updated: 2024/07/25 03:08:42 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back(t_env **lst, t_env *new_env)
{
	if (lst == NULL || new_env == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new_env;
		return ;
	}
	while ((*lst)->next != NULL)
	{
		lst = &(*lst)->next;
	}
	(*lst)->next = new_env;
}
