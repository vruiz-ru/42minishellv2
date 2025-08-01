/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freemap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 18:55:43 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/01 19:05:36 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maps.h"

void	ft_mapfree(char **map)
{
	int	i;

	if (!map || !*map)
		return ;
	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
}