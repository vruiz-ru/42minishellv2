/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 18:45:50 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/04 00:22:21 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPS_H
# define MAPS_H

# include "../strings/strings.h"
# include <limits.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

// UTILS
void	free_partial(char **map, size_t count);
char	**create_new(char **map, char *add_last);
int		copy_elements(char **map, char **new_map, size_t skip);
int		right_length(char *item);
// FUNCTIONS
size_t	ft_mapsize(char **map);
char	**ft_mapdup(char **map);
void	ft_mapfree(char ***map);
int		ft_mapitem_replace(char ***map, char *item, size_t idx);
int		ft_mapitem_del(char ***map_ref, size_t del_idx);
int		ft_mapitem_index(char **map, char *str);
int		ft_mapitem_add(char ***map_ref, char *item);
char	**ft_mapnew(char *item);

#endif