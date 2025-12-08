/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getvar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:15:42 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/09 18:14:43 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

char	*ft_getvar(char **envp, char *var_name)
{
	int		i;
	size_t	len;
	char	*value;

	if (!envp || !var_name)
		return (NULL);
	len = ft_strlen(var_name);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var_name, len) && envp[i][len] == '=')
		{
			value = ft_strdup(envp[i] + len + 1);
			if (!value)
				return (perror("malloc"), exit(EXIT_FAILURE), NULL);
			return (value);
		}
		i++;
	}
	return (NULL);
}
