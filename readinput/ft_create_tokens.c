/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 22:07:38 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/08 14:40:26 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int ft_cmd(t_subproc *process, char *line)
{
    char    *cmd;

    cmd = ft_strtok(line, " ");
    if (!cmd)
        return (perror("malloc"), 0);
    ft_lstadd_back(&process->builtins->tokens, ft_lstnew(cmd));
    return (1);
}

static char	*ft_normal(t_subproc *process, char *line)
{
	if (*line && line)
	{
        line = parse_token(process, line);
        if (!line)
            return (perror("malloc"), NULL);
		ft_lstadd_back(&process->builtins->tokens, ft_lstnew(ft_strdup(line)));
		free(line);
	}
	return (NULL);
}

int	ft_create_tokens(t_subproc *process)
{
	char	*line_args;
	int		dquote_idx;
	int		squote_idx;

    ft_printf("create_tokens1\n");
	if (!ft_cmd(process, process->line))
        return (0);
    ft_printf("create_tokens2\n");
	if (!ft_strchr(process->line, ' '))
		return (1);
    ft_printf("create_tokens3\n");
	line_args = ft_strdup(ft_strchr(process->line, ' ') + 1);
    ft_printf("create_tokens4\n");
	while (line_args)
	{
		dquote_idx = quote_pos(line_args, '"', 1);
		squote_idx = quote_pos(line_args, '\'', 1);
		ft_printf("create_tokens5\n");
        if (dquote_idx >= 0 && (squote_idx < 0 || \
			(squote_idx >= 0 && dquote_idx < squote_idx)))
			line_args = ft_quotes(process, line_args, '"');
		else if (squote_idx >= 0)
			line_args = ft_quotes(process, line_args, '\'');
		else
			line_args = ft_normal(process, line_args);
        ft_printf("create_tokens6\n");
	}
	return (1);
}
