/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safeadd_nodes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:40:35 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/03 20:58:42 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_safeadd_tokens(t_list **tokens, char **token)
{
	char	*ptr;
	char	*to_list;

	ptr = *token;
	if (!ptr || !*ptr)
	{
		if (ptr)
			free(ptr);
		*token = NULL;
		return ;
	}
	to_list = ft_strdup(ptr);
	if (!to_list)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_lstadd_back(tokens, ft_lstnew(to_list));
	free(ptr);
	*token = NULL;
}
