/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 13:50:23 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/03 21:53:25 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strings.h"

char	*ft_addchar(char *str, char ch)
{
	char	*new;
	size_t	new_size;
	size_t	i;

	if (!str || !*str)
		new_size = 1;
	else
		new_size = ft_strlen(str) + 1;
	new = malloc((new_size + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (str && str[i] != '\0')
	{
		new[i] = str[i];
		i++;
	}
	new[i++] = ch;
	new[i] = '\0';
	free(str);
	str = NULL;
	return (new);	
}
