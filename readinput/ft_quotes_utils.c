/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:28:42 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/09 12:25:56 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (str[idx] == delim && (str[idx - 1] != '\\' || slash % 2 == 0))
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

int quotes_left(t_list *tokens, char *line_left)
{
	char    *space;
	char    *temp;
	
	if (!line_left || !*line_left)
		return (0);
	if (ft_strchr(line_left, '\'') || ft_strchr(line_left, '"'))
		return (1);
	if (line_left && *line_left == ' ')
	{
		space = ft_strdup(" ");
		temp = ft_strdup(line_left + 1);
		if (!space || !temp)
			return (perror("malloc"), 0);
		ft_lstadd_back(&tokens, ft_lstnew(space));
		ft_lstadd_back(&tokens, ft_lstnew(temp));
	}
	else
	{
		temp = ft_strdup(line_left + 1);
		if (!temp)
			return (perror("malloc"), 0);
		ft_lstadd_back(&tokens, ft_lstnew(temp));
	}
	return (0);
}

int first_occurrence(t_subproc *process, char *line, char delim)
{
	char	*chunk;
	int 	idx;

	idx = quote_pos(line, delim, 1);
	if (idx < 0)
		return (-1);
	if (idx > 0)
	{
		chunk = ft_substr(line, 0, idx);
		if (!chunk)
			return(perror("malloc"), 0);
		chunk = parse_token(process, chunk, 'n');
		ft_lstadd_back(&process->builtins->tokens, ft_lstnew(chunk));
	}
	return (idx);
}
