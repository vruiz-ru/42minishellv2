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

#include "../../headers/minishell.h"
#include "../input.h"

static int	handle_error(t_process *proc, int type)
{
	if (type == 1)
	{
		ft_putstr_fd("minishell: syntax error: unclosed quotes\n", 2);
		proc->status = 2;
	}
	ft_lstclear(&proc->tokens, free);
	proc->tokens = NULL;
	return (2);
}

static int	skip_quotes(char *line, int *i)
{
	char	quote;

	quote = line[*i];
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i] == quote)
	{
		(*i)++;
		return (0);
	}
	return (1);
}

static int	get_full_len(char *line)
{
	int	i;

	if (ft_strchr("<>|", *line))
		return (1 + (ft_strchr("<>", *line) && *line == line[1]));
	i = 0;
	while (line[i] && !ft_strchr(" \t<>|", line[i]))
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			if (skip_quotes(line, &i))
				return (-1);
		}
		else
			i++;
	}
	return (i);
}

static int	add_next_token(t_process *process, char *line, int len)
{
	char	*raw;
	char	*parsed;
	t_list	*last;
	int		quoted;

	raw = ft_substr(line, 0, len);
	if (!raw)
		return (perror("malloc"), 0);
	last = ft_lstlast(process->tokens);
	if (last && !ft_strncmp(last->content, "<<", 3))
	{
		parsed = ft_parse_delimiter(raw, &quoted);
		if (quoted)
			parsed = ft_addchar(parsed, 1);
	}
	else
		parsed = ft_parse_token(process, raw, 'n');
	if (!parsed)
		return (free(raw), 0);
	ft_safeadd_tokens(&process->tokens, &parsed);
	return (1);
}

int	ft_tokenize_line(t_process *proc, char *line)
{
	int	i;
	int	len;

	i = 0;
	while (line[i])
	{
		if (ft_strchr(" \t", line[i]))
		{
			i++;
			continue ;
		}
		len = get_full_len(line + i);
		if (len == -1)
			return (handle_error(proc, 1));
		if (!add_next_token(proc, line + i, len))
			return (handle_error(proc, 0));
		i += len;
	}
	return (1);
}
