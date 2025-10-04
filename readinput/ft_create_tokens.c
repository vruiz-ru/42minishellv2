/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 22:07:38 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/04 13:19:28 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_cmd_token(t_subproc *process)
{
	char	*cmd;

	if (!process->line)
		return (0);
	cmd = ft_strtok(process->line, " ");
	ft_lstadd_back(&process->builtins->tokens, ft_lstnew(cmd));
	return (1);
}

static char	*ft_normal_token(t_list *tokens, char *line)
{
	char	*new;
	char	*res;
	int		size;
	int		length;

	
	new = ft_strtok(NULL, " ");
	if (!new)
		return (NULL);
	ft_lstadd_back(&tokens, ft_lstnew(new));
	size = ft_strlen(line);
	length = ft_strlen(new);
	res = ft_strdup(ft_strnstr(line, new, size) + length);
	free(line);
	return (res);}

char	*ft_quotes_token(t_list *tokens, char *line, char ch)
{
	char	*temp_token;
	char	delim[2];
	char	*new;
	char	*res;
	int		closed_quotes;

	delim[0] = ch;
	delim[1] = '\0';
	new = NULL;
	temp_token = ft_strtok(NULL, delim);
	if (ft_checkpair(temp_token, ch))
		new = ft_strjoin_free(new, temp_token);
	else
		new = ft_strjoin_free(temp_token, ft_strtok(NULL, delim));
	if (new == NULL)
		return (perror("malloc"), NULL);
	ft_lstadd_back(&tokens, ft_lstnew(new));
	closed_quotes = ft_strlen(new) + 1;
	res = ft_strdup(ft_strnstr(line, new, ft_strlen(line)) + closed_quotes);
	free(line);
	return (res);
}

int	ft_create_tokens(t_subproc *process)
{
	char	*line;
	int		dquote_idx;
	int		squote_idx;

	if (!ft_cmd_token(process))
		return (0);
	if (!ft_strchr(process->line, ' '))
		return (1);
	line = ft_strdup(ft_strchr(process->line, ' ') + 1);
	while (*line && line)
	{
		dquote_idx = ft_getquote_idx(line, '"');
		squote_idx = ft_getquote_idx(line, '\'');
		if (dquote_idx >= 0 && \
			(squote_idx < 0 || \
			(squote_idx >= 0 && dquote_idx < squote_idx)))
			line = ft_quotes_token(process->builtins->tokens, line, '"');
		else if (squote_idx >= 0)
			line = ft_quotes_token(process->builtins->tokens, line, '\'');
		else
			line = ft_normal_token(process->builtins->tokens, line);
	}
	return (1);
}
