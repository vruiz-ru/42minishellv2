/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 18:55:43 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/03 21:01:57 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maps.h"

void	ft_mapfree(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
    {
        free(map[i]);
        i++;
    }
	free(map);
}