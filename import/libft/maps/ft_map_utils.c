/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:15:01 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/03 23:06:11 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maps.h"

void	free_partial(char **map, size_t count)
{
	if (!map)
		return;
	while (count > 0)
	{
		count--;
		free(map[count]);
	}
}

char	**create_new(char **map, char *add_last)
{
	char    **new_map;
	int		i;

	new_map = malloc((ft_mapsize(map) + 2) * sizeof(char *));
	if (!new_map)
		return (NULL);
	i = 0;
	while (map[i])
	{
		new_map[i] = ft_strdup(map[i]);
		if (!new_map[i])
			return (free_partial(new_map, i), free(new_map), NULL);
		i++;
	}
	new_map[i] = ft_strdup(add_last);
	if (new_map[i] == NULL)
		return (free_partial(new_map, i),  free(new_map), NULL);
	new_map[i + 1] = NULL;
	return (new_map);
}

int	copy_elements(char **map, char **new_map, size_t skip)
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
			return (free_partial(new_map, j), free(new_map), 0);
		j++;
		i++;
	}
	new_map[j] = NULL;
	return (1);
}

int	right_length(char *item)
{
	char	*ptr;
	
	ptr = ft_strchr(item, '=');
	if (ptr)
		return (ptr - item);
	return (ft_strlen(item));
}
