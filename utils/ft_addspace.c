/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addspace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:18:47 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/03 20:57:43 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_addspace(t_list **tokens)
{
	char	*to_add;

	if (*tokens == NULL)
		return ;
	to_add = ft_strdup(" ");
	if (!to_add)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_safeadd_tokens(tokens, &to_add);
}
