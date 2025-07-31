/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:31:19 by aghergut          #+#    #+#             */
/*   Updated: 2025/07/23 15:15:43 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strings.h"

size_t	ft_strlcat(char	*dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	src_idx;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (len_dst > size)
		return (size + len_src);
	src_idx = 0;
	while (len_dst < size && src[src_idx] != '\0')
		dst[len_dst++] = src[src_idx++];
	if (len_dst + len_src >= size)
	{
		if (len_dst < size)
			dst[size - 1] = '\0';
		return (len_dst + len_src);
	}
	dst[len_dst] = '\0';
	return (ft_strlen(dst));
}
