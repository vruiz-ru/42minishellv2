/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:54:08 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/09 17:59:26 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	parse_redir(t_cmd *node, char *redir, char *file)
{
	int	heredoc_fd;

	if (!ft_strncmp(redir, "<<", 3))
	{
		heredoc_fd = ft_heredoc(file);
		ft_add_io(node, IO_HEREDOC, "heredoc", heredoc_fd);
	}
	else if (!ft_strncmp(redir, ">>", 3))
		ft_add_io(node, IO_APPEND, file, -1);
	else if (!ft_strncmp(redir, "<", 2))
		ft_add_io(node, IO_IN, file, -1);
	else if (!ft_strncmp(redir, ">", 2))
		ft_add_io(node, IO_OUT, file, -1);
}

static int	count_args(t_list *tokens)
{
	int		i;
	char	*str;

	i = 0;
	while (tokens && ((char *)tokens->content)[0] != '|')
	{
		str = (char *)tokens->content;
		if (is_redir(str))
		{
			tokens = tokens->next;
			while (tokens && !ft_strncmp(tokens->content, " ", 2))
				tokens = tokens->next;
		}
		else if (ft_strncmp(str, " ", 2) != 0)
			i++;
		if (tokens)
			tokens = tokens->next;
	}
	return (i);
}
/*
static void	fill_cmd(t_cmd *node, t_list **tokens)
{
	int		i;
	char	*str;

	i = 0;
	while (*tokens && ((char *)(*tokens)->content)[0] != '|')
	{
		str = (char *)(*tokens)->content;
		if (is_redir(str))
		{
			*tokens = (*tokens)->next;
			while (*tokens && !ft_strncmp((*tokens)->content, " ", 2))
				*tokens = (*tokens)->next;
			if (*tokens)
				parse_redir(node, str, (char *)(*tokens)->content);
		}
		else if (ft_strncmp(str, " ", 2) != 0)
			node->args[i++] = ft_strdup(str);
		if (*tokens)
			*tokens = (*tokens)->next;
	}
	node->args[i] = NULL;
}*/
static int	is_separator(char *str)
{
	if (is_redir(str) || !ft_strncmp(str, " ", 2) || str[0] == '|')
		return (1);
	return (0);
}

static void	fill_cmd(t_cmd *node, t_list **tokens)
{
	int		i;
	char	*accum;
	char	*temp;

	i = 0;
	while (*tokens && ((char *)(*tokens)->content)[0] != '|')
	{
		if (is_redir((*tokens)->content))
		{
			char *redir = (*tokens)->content;
			*tokens = (*tokens)->next;
			while (*tokens && !ft_strncmp((*tokens)->content, " ", 2))
				*tokens = (*tokens)->next;
			if (*tokens)
				parse_redir(node, redir, (char *)(*tokens)->content);
			if (*tokens) *tokens = (*tokens)->next;
		}
		else if (!ft_strncmp((*tokens)->content, " ", 2))
		{
			*tokens = (*tokens)->next; // Ignorar espacios sueltos
		}
		else
		{
			// Concatenación Segura
			accum = ft_strdup("");
			while (*tokens && !is_separator((*tokens)->content))
			{
				temp = ft_strjoin(accum, (*tokens)->content);
				free(accum);
				accum = temp;
				*tokens = (*tokens)->next;
			}
			node->args[i++] = accum;
		}
	}
	node->args[i] = NULL;
}

static t_cmd	*create_one_cmd(t_list **tokens)
{
	t_cmd	*new;

	new = ft_new_cmd();
	if (!new)
		return (NULL);
	new->args = malloc(sizeof(char *) * (count_args(*tokens) + 1));
	if (!new->args)
	{
		free(new);
		return (NULL);
	}
	fill_cmd(new, tokens);
	return (new);
}

int	ft_tokens_to_cmds(t_process *process)
{
	t_list	*curr;
	t_cmd	*new_node;

	curr = process->tokens;
	while (curr)
	{
		if (!ft_strncmp(curr->content, " ", 2)
			|| ((char *)curr->content)[0] == '|')
		{
			curr = curr->next;
			continue ;
		}
		new_node = create_one_cmd(&curr);
		if (!new_node)
			return (0);
		ft_cmdadd_back(&process->commands, new_node);
	}
	return (1);
}
