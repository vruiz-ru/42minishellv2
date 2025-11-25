/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getcwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 08:24:29 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/02 18:52:55 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

char	*ft_getcwd(void)
{
	char	cwd[4096];
	char	*res;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (NULL); 
	res = ft_strdup(cwd);
	if (!res)
		return (perror("malloc"), NULL);
	return (res);
}
