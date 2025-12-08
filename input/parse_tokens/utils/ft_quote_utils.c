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

static void	process_pre_quote(t_process *proc, char *chunk)
{
	char	*token;
	char	*next_token;
	char	*parsed;

	if (!chunk)
		return ;
	token = ft_strtok(chunk, " ");
	while (token)
	{
		parsed = ft_parse_token(proc, token, 'n');
		ft_safeadd_tokens(&proc->tokens, &parsed);
		next_token = ft_strtok(NULL, " ");
		if (next_token)
			ft_addspace(&proc->tokens);
		token = next_token;
	}
	free(chunk);
}

static int	skip_backslashes(char *str, int *idx)
{
	int	slash;

	slash = 0;
	while (str[*idx] == '\\')
	{
		slash++;
		(*idx)++;
	}
	return (slash);
}

int	quote_pos(char *str, char delim, int times)
{
	int	idx;
	int	found;
	int	slash;

	idx = 0;
	found = 0;
	while (str[idx])
	{
		slash = skip_backslashes(str, &idx);
		if (!str[idx])
			break ;
		if (str[idx] == delim && (idx == 0 || str[idx - 1] != '\\' || slash
				% 2 == 0))
		{
			found++;
			if (found == times)
				return (idx);
		}
		idx++;
	}
	return (-1);
}

int	first_occurrence(t_process *process, char *line, char delim)
{
	char	*chunk;
	int		idx;
	int		len;

	idx = quote_pos(line, delim, 1);
	if (idx <= 0)
		return (idx);
	len = idx;
	if (check_ansi_quote(line, idx, delim))
		len = idx - 1;
	chunk = ft_substr(line, 0, len);
	if (!chunk)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	process_pre_quote(process, chunk);
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
