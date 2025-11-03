/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapitem_del.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:16:51 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/03 21:16:49 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maps.h"

int	ft_mapitem_del(char ***map_ref, size_t del_idx)
{
	char	**new_map;
	char	**temp;
	size_t	length;

	if (!map_ref || !*map_ref)
		return (0);
	temp = *map_ref;
	length = ft_mapsize(temp);
	if (del_idx >= length)
		return (0);
	new_map = (char **)malloc(length * sizeof(char *));
	if (!new_map)
		return (0);
	if (!copy_elements(temp, new_map, del_idx))
		return (ft_mapfree(new_map), 0);
	ft_mapfree(temp);
	*map_ref = new_map;
	return (1);
}

