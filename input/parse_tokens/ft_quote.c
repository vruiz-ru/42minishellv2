/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 08:02:00 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/03 20:52:15 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../input.h"

static int reconstruct_token(t_process *process, char *line, char delim)
{
	char	*res;
	int		start_idx;
	int		end_idx;

	start_idx = first_occurrence(process, line, delim);
	if (start_idx < 0)
		return (-1);
	start_idx += 1;
	end_idx = quote_pos(line, delim, 2) - start_idx;
	res = ft_substr(line, start_idx, end_idx);
	if (!res)
		return (perror("malloc"), exit(EXIT_FAILURE), 0);
	if (delim == '"')
		res = ft_parse_token(process, res, 'd');
	ft_safeadd_tokens(&process->tokens, &res);
	return (1);
}

/* FUNCIÓN CORREGIDA: Calcula el avance real saltando espacios */
static char	*standard_token(t_process *process, char *line)
{
	char	*added;
	char	*line_left;
	int		i;
	int		len;

	// 1. Saltar espacios iniciales para saber dónde empieza el token real
	i = 0;
	while (line[i] == ' ')
		i++;
	
	// 2. Calcular longitud del token (hasta el siguiente espacio o fin)
	len = 0;
	while (line[i + len] && line[i + len] != ' ')
		len++;
	
	// 3. Extraer el token
	added = ft_substr(line, i, len);
	if (!added)
		return (perror("malloc"), exit(EXIT_FAILURE), NULL);
	
	// 4. Parsearlo y añadirlo
	added = ft_parse_token(process, added, 'n');
	if (!added)
		return (free(line), NULL);
	ft_safeadd_tokens(&process->tokens, &added);

	// 5. Calcular el resto de la línea
	if (line[i + len])
	{
		line_left = ft_strdup(line + i + len);
		if (!line_left)
			return (perror("malloc"), exit(EXIT_FAILURE), NULL);
		ft_addspace(&process->tokens);
		free(line);
		return (line_left);
	}
	free(line);
	return (NULL);
}

static char	*quotes_token(t_process *process, char *line, char delim)
{
	char	*line_left;
	int		indexes_left;
	int		last_index;
	int		paired_delim;
	
	line_left = NULL;
	if (reconstruct_token(process, line, delim) < 0)
		return (NULL);
	indexes_left = 0;
	last_index = ft_strlen(line) - 1;
	paired_delim = quote_pos(line, delim, 2);
	if (paired_delim < last_index)
		indexes_left = last_index - paired_delim;
	if (indexes_left > 0)
	{
		line_left = ft_substr(line, paired_delim + 1, indexes_left);
		if (!line_left)
			return (perror("malloc"), exit(EXIT_FAILURE), NULL);
		if (line_left[0] == ' ')
			ft_addspace(&process->tokens);
	}
	return (free(line), line_left);
}

int	ft_quote(t_process *process, char *line)
{
	char	*line_args;
    char    delimiter;

    if (ft_strchr(line, ' ') && process->is_variable == false)
		line_args = ft_strdup(ft_strchr(line, ' ') + 1);
	else
		line_args = ft_strdup(line);
	if (!line_args)
		return (perror("malloc"), exit(EXIT_FAILURE), 0);
    ft_clear_strtok();
    while (line_args && *line_args)
	{
		delimiter = quote_delimiter(line_args);
        if (delimiter == 0)
            line_args = standard_token(process, line_args);
        else
            line_args = quotes_token(process, line_args, delimiter);
	}		
	return (1);
}
