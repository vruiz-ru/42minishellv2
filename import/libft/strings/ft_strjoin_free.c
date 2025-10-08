/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:32:53 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/08 10:38:24 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strings.h"

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	size_t	i;
	size_t	join_i;
	char	*join;

	if (!s2)
		return (NULL);
	if (!s1)
	{
		join = ft_substr(s2, 0, ft_strlen(s2));
		if (!join)
			return (free((void *)s2), s2 = NULL, NULL);
		return (free((void *)s2), s2 = NULL, join);
	}
	join = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) +1) * sizeof(char));
	if (!join)
		return (free((void *)s1), free((void *)s2), NULL);
	join_i = -1;
	while (s1[++join_i] != '\0')
		join[join_i] = s1[join_i];
	i = 0;
	while (s2[i] != '\0')
		join[join_i++] = s2[i++];
	join[join_i] = '\0';
	return (free((void *)s1), s1 = NULL, free((void *)s2), s2 = NULL, join);
}
