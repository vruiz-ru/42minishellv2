/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapreplace_item.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:08:38 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/01 19:16:22 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maps.h"

char	**ft_mapreplace_item(char **map, char *item, size_t n)
{
	size_t	idx;

	if (!map || !*map || ft_mapsize(map) < n)
		return (NULL);
	idx = n - 1;
	if (map[idx] != NULL)
		free(map[idx]);
	map[idx] = ft_strdup(item);
	if (!map[idx])
		return (NULL);
	return (map);
}
