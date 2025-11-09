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
	char	*value;
	int		name_length;
	int		i;

	i = 0;
	value = NULL;
	while (envp[i])
	{
		name_length = ft_strchr(envp[i], '=') - envp[i] - 1;
		if (name_length && !ft_strncmp(envp[i], var_name, name_length))
		{
			if (envp[i][name_length + 2])
			{
				value = ft_strdup(envp[i] + name_length + 2);
				if (!value)
					return (perror("malloc"), exit(EXIT_FAILURE), NULL);
			}
			else
				break ;
			return (value);
		}
		i++;
	}
	return (NULL);
}
