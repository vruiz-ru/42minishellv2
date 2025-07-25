/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:15:42 by aghergut          #+#    #+#             */
/*   Updated: 2025/07/24 13:03:45 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* find only if the variable exists in the environment

int is_variable(char *envp[], char *var_name)
{
	char	**split;
	int		i;

	i = 0;
	while (envp[i])
	{
		split = ft_split(envp[i], "=");
		if (!ft_strncmp(split[0], var_name, ft_strlen(var_name)))
			return (free_map(split), 1);
		free_map(split);
		split = NULL;
		i++;
	}
	return (0);
}
*/

char	*get_variable(char *envp[], char *var_name)
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
			value = ft_strdup(split[1]);
			free_map(split);
			return (value);
		}
		free_map(split);
		split = NULL;
		i++;
	}
	return ("");
}
