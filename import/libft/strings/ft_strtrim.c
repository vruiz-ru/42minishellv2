/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:22:05 by aghergut          #+#    #+#             */
/*   Updated: 2025/07/23 15:24:03 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strings.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		res_length;
	int		s1_length;
	int		front_idx;
	int		back_idx;

	if (!s1 || !set)
		return (NULL);
	s1_length = ft_strlen(s1);
	front_idx = 0;
	back_idx = s1_length - 1;
	while (s1[front_idx] && ft_strchr(set, s1[front_idx]))
		front_idx++;
	while (back_idx >= front_idx && ft_strchr(set, s1[back_idx]))
		back_idx--;
	if (front_idx == 0 && back_idx == s1_length - 1)
		return (ft_strdup(s1));
	res_length = back_idx - front_idx + 1;
	if (res_length < 1)
		return (ft_strdup(""));
	res = ft_substr(s1, front_idx, res_length);
	return (res);
}
