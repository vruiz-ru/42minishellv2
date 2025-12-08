/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 11:17:23 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/02 11:20:45 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maps.h"

char	**ft_mapnew(char *item)
{
	char	**map;

	if (!item)
		return (NULL);
	map = malloc(2 * sizeof(char *));
	if (!map)
		return (NULL);
	map[0] = ft_strdup(item);
	if (!map[0])
		return (free(map), NULL);
	map[1] = NULL;
	return (map);
}
