/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 18:41:48 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/01 19:05:17 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maps.h"

char	**ft_mapdup(char **map)
{
	char	**dup;
	size_t	length;
	int		i;

	length = ft_mapsize(map);
	if (!length)
		return (NULL);
	dup = (char **)malloc((length + 1) * sizeof(char *));
	if (!dup)
		return (NULL);
	i = -1;
	while (map[++i])
	{
		dup[i] = ft_strdup(map[i]);
		if (!dup[i])
		{
			while (--i >= 0)
				free(dup[i]);
			return (free(dup), NULL);
		}
	}
	dup[i] = NULL;
	return (dup);
}
