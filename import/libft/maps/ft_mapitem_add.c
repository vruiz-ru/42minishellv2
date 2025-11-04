/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapitem_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 10:49:39 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/04 00:30:42 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maps.h"

int	ft_mapitem_add(char ***map_ref, char *item)
{
	char	**map;
	char	**new;

	if (!map_ref)
		return (0);
	map = *map_ref;
	if (map == NULL)
	{
		*map_ref = ft_mapnew(item);
		if (*map_ref == NULL)
			return (0);
		return (1);
	}
	new = create_new(map, item);
	if (new != NULL)
	{
		ft_mapfree(map_ref);
		*map_ref = new;
		return (1);	
	}
	return (0);
}
