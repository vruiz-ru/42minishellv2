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

/* Salta hasta cerrar comilla */
static void	skip_quotes(char *line, int *i)
{
	char	quote;

	quote = line[*i];
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i] == quote)
		(*i)++;
}

/* Mide la palabra completa respetando comillas pegadas */
static int	get_token_len(char *line)
{
	int	i;

	i = 0;
	while (line[i] && !ft_strchr(" \t<>|", line[i])) // Paramos en espacios o redirs
	{
		if (line[i] == '\'' || line[i] == '"')
			skip_quotes(line, &i);
		else
			i++;
	}
	return (i);
}

/* Sustituye tu static add_next_token por esta versión: */
static int	add_next_token(t_process *process, char *line, int len)
{
	char	*raw;
	char	*parsed;
	t_list	*last;
	int		quoted;

	raw = ft_substr(line, 0, len);
	if (!raw)
		return (perror("malloc"), 0);
	
	// ¿El último token fue un redireccionador de heredoc?
	last = ft_lstlast(process->tokens);
	if (last && !ft_strncmp(last->content, "<<", 3))
	{
		// Usamos el parser especial para delimitadores
		parsed = ft_parse_delimiter(raw, &quoted);
		if (quoted)
			parsed = ft_addchar(parsed, 1); // MARCA MÁGICA: Hay comillas
	}
	else
	{
		// Token normal
		parsed = ft_parse_token(process, raw, 'n');
	}

	if (!parsed)
		return (free(raw), 0);
	ft_safeadd_tokens(&process->tokens, &parsed);
	return (1);
}

/* Tokeniza linealmente: Palabras completas -> Tokens limpios */
int	ft_tokenize_line(t_process *process, char *line)
{
	int	i;
	int	len;

	i = 0;
	while (line[i])
	{
		while (line[i] && ft_strchr(" \t", line[i])) // Saltar espacios
			i++;
		if (!line[i])
			break ;
		if (ft_strchr("<>|", line[i])) // Separadores especiales
		{
			len = 1;
			if ((line[i] == '<' && line[i + 1] == '<') || \
				(line[i] == '>' && line[i + 1] == '>'))
				len = 2;
			if (!add_next_token(process, line + i, len))
				return (0);
			i += len;
		}
		else // Palabras normales
		{
			len = get_token_len(line + i);
			if (!add_next_token(process, line + i, len))
				return (0);
			i += len;
		}
	}
	return (1);
}