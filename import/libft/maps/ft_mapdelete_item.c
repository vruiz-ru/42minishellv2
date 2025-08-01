/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapdelete_item.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:16:51 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/01 20:46:59 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maps.h"

static void	free_partial(char **map, size_t from_index)
{
	if (!map)
		return;
	while (from_index > 0)
		free(map[--from_index]);
	free(map);
}

static int	copy_elements(char **map, char **new_map, size_t skip)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (map[i] != NULL)
	{
		if (i == skip)
		{
			i++;
			continue;
		}
		new_map[j] = ft_strdup(map[i]);
		if (!new_map[j])
		{
			free_partial(new_map, j);
			return (0);
		}
		j++;
		i++;

	}
	new_map[j] = NULL;
	return (1);
}

char	**ft_mapdelete_item(char **map, size_t del_idx)
{
	char	**new_map;
	size_t	length;
	
	if (!map || !*map)
		return (NULL);
	length = ft_mapsize(map);
	if (del_idx >= length)
		return (NULL);
	new_map = (char **)malloc(length * sizeof(char *));
	if (!new_map)
		return (NULL);
	if (copy_elements(map, new_map, del_idx))
	{
		ft_mapfree(map);
		return (new_map);
	}
	return (NULL);
}
