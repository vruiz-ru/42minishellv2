/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getvar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:15:42 by aghergut          #+#    #+#             */
/*   Updated: 2025/07/31 20:10:29 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_variable(char *envp[], char *var_name)
{
	char	**split;
	int		i;

	i = 0;
	while (envp[i])
	{
		split = ft_split(envp[i], '=');
		if (!ft_strncmp(split[0], var_name, ft_strlen(var_name)))
			return (free_map(split), 1);
		free_map(split);
		split = NULL;
		i++;
	}
	return (0);
}

char	*ft_getvar(char *envp[], char *var_name)
{
	char	**split;
	char	*value;
	int		i;

	i = 0;
	split = NULL;
	value = NULL;
	while (envp[i])
	{
		split = ft_split(envp[i], '=');
		if (!ft_strncmp(split[0], var_name, ft_strlen(var_name)))
		{
            if (split[1])
			    value = ft_strdup(split[1]);
			else
                value = ft_strdup("");
            free_map(split);
			return (value);
		}
		free_map(split);
		split = NULL;
		i++;
	}
	return ("");
}
