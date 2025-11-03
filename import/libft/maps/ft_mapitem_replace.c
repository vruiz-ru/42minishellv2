/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapitem_replace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:08:38 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/03 21:20:28 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maps.h"

int	ft_mapitem_replace(char ***map, char *item, size_t idx)
{
	char    *temp;
	
	if (!map || !*map || ft_mapsize(*map) <= idx)
		return (0);
	temp = ft_strdup(item);
	if (!temp)
		return (0);
	if ((*map)[idx])
		free((*map)[idx]);
	(*map)[idx] = temp;
	return (1);
}
