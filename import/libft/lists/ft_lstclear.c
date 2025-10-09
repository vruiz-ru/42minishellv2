/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:45:40 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/09 12:35:01 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ptr;
	t_list	*temp;

	if (lst)
	{
		ptr = *lst;
		while (ptr != NULL)
		{
			temp = ptr->next;
			ft_lstdelone(ptr, del);
			ptr = temp;
		}
		*lst = NULL;
	}
}
