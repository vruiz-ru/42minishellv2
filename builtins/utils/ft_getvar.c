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

/*
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
}*/
char	*ft_getvar(char **envp, char *var_name)
{
	char	*value;
	size_t	name_len_env;
	size_t	var_name_len;
	int		i;

	if (!envp || !var_name)
		return (NULL);
	var_name_len = ft_strlen(var_name);
	i = 0;
	while (envp[i])
	{
		// CORRECCIÓN MATEMÁTICA: La longitud es puntero_igual - puntero_inicio
		if (ft_strchr(envp[i], '='))
			name_len_env = ft_strchr(envp[i], '=') - envp[i];
		else
			name_len_env = ft_strlen(envp[i]);

		// CORRECCIÓN LÓGICA: Comprobamos longitud exacta Y contenido
		if (name_len_env == var_name_len && \
			!ft_strncmp(envp[i], var_name, name_len_env))
		{
			// Si tiene valor, lo devolvemos
			if (envp[i][name_len_env] == '=')
			{
				value = ft_strdup(envp[i] + name_len_env + 1);
				if (!value)
					return (perror("malloc"), exit(EXIT_FAILURE), NULL);
				return (value);
			}
			return (NULL);
		}
		i++;
	}
	return (NULL);
}