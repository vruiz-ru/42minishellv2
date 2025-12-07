/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:28:42 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/03 22:09:44 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../input.h"

static void	quote_pos_aux(char **str, int *idx, int *slash)
{
	while ((*str)[*idx] == '\\')
	{
		(*slash)++;
		(*idx)++;
	}   
}

int	quote_pos(char *str, char delim, int times)
{
	int	idx;
	int	occurrence;
	int quote_idx;
	int slash;
	
	quote_idx = -1;
	idx = 0;
	occurrence = 0;
	while (str[idx])
	{
		slash = 0;
		quote_pos_aux(&str, &idx, &slash);
		if (!str[idx])
			break;
		if (str[idx] == delim && \
            (idx == 0 || str[idx - 1] != '\\' || slash % 2 == 0))
		{
			occurrence++;
			quote_idx = idx;
		}
		if (occurrence == times)
			break;
		idx++;
	}
	// <--- FIX CRÍTICO: Si no encontramos las 'times' ocurrencias, fallamos
	if (occurrence < times)
		return (-1);
	// ---------------------------------------------------------------------
	return (quote_idx);
}

int	first_occurrence(t_process *process, char *line, char delim)
{
	char	*chunk;
	char	*token;
	char	*parsed;
	int		idx;
	int     len;

	idx = quote_pos(line, delim, 1);
	if (idx < 0)
		return (-1);
	if (idx > 0)
	{
		len = idx;
		// CORRECCIÓN: Usamos la función externa para recortar el $ si es $'
		if (check_ansi_quote(line, idx, delim))
			len = idx - 1;

		chunk = ft_substr(line, 0, len);
		if (!chunk)
			return (perror("malloc"), exit(EXIT_FAILURE), 0);
		
		token = ft_strtok(chunk, " ");
		while (token)
		{
			parsed = ft_parse_token(process, token, 'n');
			ft_safeadd_tokens(&process->tokens, &parsed);
			ft_addspace(&process->tokens); // Añadimos separador
			token = ft_strtok(NULL, " ");
		}
		free(chunk);
	}
	return (idx);
}

char	quote_delimiter(char *line)
{
	int	d_start;
	int	s_start;
	int	d_end;
	int	s_end;

	d_start = quote_pos(line, '"', 1);
	s_start = quote_pos(line, '\'', 1);
	d_end = -1;
	s_end = -1;
	if (d_start >= 0)
		d_end = quote_pos(line, '"', 2);
	if (s_start >= 0)
		s_end = quote_pos(line, '\'', 2);
	if (d_end == -1)
		d_start = -1;
	if (s_end == -1)
		s_start = -1;
	if (d_start >= 0 && (s_start < 0 || d_start < s_start))
		return ('"');
	if (s_start >= 0)
		return ('\'');
	return (0);
}
