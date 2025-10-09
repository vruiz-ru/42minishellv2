/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 22:07:38 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/09 12:54:37 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*parse_token(t_subproc *process, char *content, char token)
{
	char	*res;
	char	*var_name;
	int		i;

	i = 0;
	content = clean_line(content, token);
	res = NULL;
	while (content[i] != '\0')
	{
		var_name = NULL;
		scan_char(content, &var_name, &i);
		if (var_name != NULL)
		{
			insert_value(process, &res, var_name);
			if (!res)
				return (NULL);
            free(var_name);
		}
		res = ft_addchar(res, content[i]);
		i++;
	}
	return (free(content), res);	
}

static int reconstruct_token(t_subproc *process, char *line, char delim)
{
	t_list	**tokens;
	char	*res;
	int		start_idx;
	int		end_idx;

	tokens = &process->builtins->tokens;
	start_idx = first_occurrence(process, line, delim);
	if (start_idx < 0)
		return (-1);
	end_idx = quote_pos(line, delim, 2);
	res = ft_substr(line, start_idx + 1, end_idx - (start_idx + 1));
	if (!res)
		return (perror("malloc"), 0);
	if (delim == '"')
		res = parse_token(process, res, 'd');
	ft_lstadd_back(tokens, ft_lstnew(res));
	return (1);
}

static char	*normal_token(t_subproc *process, char *line, char type)
{
	char	*cmd;
	
	if (type == 'c')
	{
		cmd = ft_strtok(line, " ");
		if (!cmd)
			return (perror("malloc"), NULL);
		return (cmd);
	}
	if (*line && line)
	{
		line = parse_token(process, line, 'n');
		if (!line)
			return (perror("malloc"), NULL);
		ft_lstadd_back(&process->builtins->tokens, ft_lstnew(ft_strdup(line)));
	}
	return (line);
}

static char	*quotes_token(t_subproc *process, char *line, char delim)
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
			return (perror("malloc"), NULL);
	}
	if (quotes_left(process->builtins->tokens, line_left))
		return (free(line), line_left);
	return (free(line), free(line_left), NULL);
}

int	ft_create_tokens(t_subproc *process)
{
	char	*cmd;
	char	*line_args;
	int		dquote_idx;
	int		squote_idx;

	cmd = normal_token(process, process->line, 'c');
	if (!cmd)
		return (0);
	ft_lstadd_back(&process->builtins->tokens, ft_lstnew(cmd));
	if (!ft_strchr(process->line, ' '))
		return (1);
	line_args = ft_strdup(ft_strchr(process->line, ' ') + 1);
	while (line_args)
	{
		dquote_idx = quote_pos(line_args, '"', 1);
		squote_idx = quote_pos(line_args, '\'', 1);
		if (dquote_idx >= 0 && (squote_idx < 0 || \
			(squote_idx >= 0 && dquote_idx < squote_idx)))
			line_args = quotes_token(process, line_args, '"');
		else if (squote_idx >= 0)
			line_args = quotes_token(process, line_args, '\'');
		else
			line_args = normal_token(process, line_args, 'n');
	}
	return (1);
}
