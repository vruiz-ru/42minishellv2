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
	return (quote_idx);
}

int quotes_left(char *line_left)
{
	if (!line_left || !*line_left)
		return (0);
	if (ft_strchr(line_left, '\'') || ft_strchr(line_left, '"'))
		return (1);
	return (0);
}

int	first_occurrence(t_process *process, char *line, char delim)
{
	char	*chunk;
	char	*token;
	char	*parsed;
	int		idx;

	idx = quote_pos(line, delim, 1);
	if (idx < 0)
		return (-1);
	if (idx > 0)
	{
		chunk = ft_substr(line, 0, idx);
		if (!chunk)
			return (perror("malloc"), exit(EXIT_FAILURE), 0);
		
		// Troceamos el bloque previo por espacios
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
	int	dquote;
	int	squote;

	dquote = quote_pos(line, '"', 1);
	squote = quote_pos(line, '\'', 1);
	if (dquote >= 0 && (squote < 0 || (squote >= 0 && dquote < squote)))
		return ('"');
	else if (squote >= 0)
		return ('\'');	
	return (0);
}
