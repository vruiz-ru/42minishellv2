/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 18:43:31 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/01 18:55:16 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maps.h"

size_t	ft_mapsize(char **map)
{
	size_t	i;

	i = 0;
	if (!map || !*map)
		return (0);
	while (map[i] != NULL)
		i++;
	return (i);
}
