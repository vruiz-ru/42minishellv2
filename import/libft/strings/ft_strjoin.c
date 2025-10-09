/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:19:18 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/09 12:36:33 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strings.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	len;
	int		i;
	int		j;	

	if (s1 && s2)
	{
		len = ft_strlen(s1) + ft_strlen(s2);
		res = (char *) malloc((len + 1) * sizeof(char));
		if (res == NULL)
			return (NULL);
		i = -1;
		while (s1[++i])
			res[i] = s1[i];
		j = 0;
		while (s2[j])
			res[i++] = s2[j++];
		res[i] = '\0';
		return (res);
	}
	return (0);
}
