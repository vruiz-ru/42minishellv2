/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:00:47 by aghergut          #+#    #+#             */
/*   Updated: 2025/07/23 13:11:31 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strings.h"

void	ft_strncat(char *dest, char *src, size_t n)
{
	size_t	i;
	size_t	dest_index;

	if (!dest || !src)
		return ;
	i = 0;
	dest_index = ft_strlen(dest);
	while (i < n && src[i])
		dest[dest_index++] = src[i++];
	dest[dest_index] = '\0';
}
