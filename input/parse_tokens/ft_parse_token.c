/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:51:17 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/02 21:43:48 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../input.h"

static int	parse_aux(t_process *process, char **res, char **var_name)
{
	if (process->is_special == false)
	{
		insert_value(process, res, *var_name);
		free(*var_name);
		*var_name = NULL;
	}
	else
	{
		*res = ft_strjoin_free(*res, *var_name);
		*var_name = NULL;
	}
	
	// <--- FIX CRÍTICO: Si la variable no existe, res es NULL.
	// Esto NO es un error, es una cadena vacía.
	if (!*res)
		*res = ft_strdup(""); // Asignamos vacío para continuar
	
	if (!*res) // Si falla el strdup, entonces sí es error
		return (0);
	return (1);
}

char	*ft_parse_token(t_process *process, char *content, char token)
{
	char	*res;
	char	*var_name;
	int		i;

	if (!content || !*content)
		return (NULL);
	content = clean_line(content, token);
	res = NULL;
	i = 0;
	while (content[i] != '\0')
	{
		var_name = NULL;
		scan_char(process, content, &var_name, &i);
		if (var_name == NULL)
		{
			res = ft_addchar(res, content[i]);
			i++;
		}
		else if (!parse_aux(process, &res, &var_name))
            return (perror("malloc"), exit(EXIT_FAILURE), NULL);
			
	}
	return (free(content), res);	
}
