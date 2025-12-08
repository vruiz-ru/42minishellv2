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

static int	reconstruct_token(t_process *process, char *line, char delim)
{
	char	*res;
	int		start_idx;
	int		end_idx;

	start_idx = first_occurrence(process, line, delim);
	if (start_idx < 0)
		return (-1);
	if (check_heredoc_trigger(process->tokens))
		process->in_heredoc = true;
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

static char	*standard_token(t_process *process, char *line)
{
	char	*added;
	int		i;
	int		len;

	i = 0;
	while (line[i] == ' ')
		i++;
	len = 0;
	while (line[i + len] && line[i + len] != ' ')
		len++;
	added = ft_substr(line, i, len);
	if (!added)
		return (perror("malloc"), exit(EXIT_FAILURE), NULL);
	added = ft_parse_token(process, added, 'n');
	if (!added)
		return (free(line), NULL);
	ft_safeadd_tokens(&process->tokens, &added);
	if (!line[i + len])
		return (free(line), NULL);
	ft_addspace(&process->tokens);
	added = ft_strdup(line + i + len);
	if (!added)
		return (perror("malloc"), exit(EXIT_FAILURE), NULL);
	return (free(line), added);
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

static char	*process_next_token(t_process *process, char *line, int next_hd)
{
	char	delim;

	delim = quote_delimiter(line);
	if (delim == 0)
	{
		process->in_heredoc = false;
		return (standard_token(process, line));
	}
	if (next_hd)
		process->in_heredoc = true;
	else
		process->in_heredoc = false;
	return (quotes_token(process, line, delim));
}

int	ft_quote(t_process *process, char *line)
{
	char	*line_args;
	int		next_is_heredoc;

	if (ft_strchr(line, ' ') && process->is_variable == false)
		line_args = ft_strdup(ft_strchr(line, ' ') + 1);
	else
		line_args = ft_strdup(line);
	if (!line_args)
		return (perror("malloc"), exit(EXIT_FAILURE), 0);
	ft_clear_strtok();
	next_is_heredoc = 0;
	while (line_args && *line_args)
	{
		line_args = process_next_token(process, line_args, next_is_heredoc);
		process->in_heredoc = false;
		next_is_heredoc = check_heredoc_trigger(process->tokens);
	}
	return (1);
}
