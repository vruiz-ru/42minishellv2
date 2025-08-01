/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapitem_index.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 20:12:06 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/01 20:25:28 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maps.h"

int  ft_mapitem_index(char **map, char *str)
{
	size_t  idx;
	size_t  n;

	if (!map || !*map || !str || !*str)
		return (-1);
	idx = 0;
	while (map[idx])
	{
		n = ft_strlen(map[idx]);
		if (!ft_strncmp(map[idx], str, n))
			return (idx);
		idx++;
	}
	return (-1);
}
