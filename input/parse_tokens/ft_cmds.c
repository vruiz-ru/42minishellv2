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

static void	parse_redir(t_cmd *node, char *redir, char *file, t_process *proc)
{
	int	heredoc_fd;
	int	expand;
	int	len;

	if (!ft_strncmp(redir, "<<", 3))
	{
		expand = 1;
		len = ft_strlen(file);
		if (len > 0 && file[len - 1] == 1)
		{
			expand = 0;
			file[len - 1] = '\0';
		}
		heredoc_fd = ft_heredoc(file, expand, proc);
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
			if (tokens)
				tokens = tokens->next;
		}
		else
		{
			i++;
			tokens = tokens->next;
		}
	}
	return (i);
}

static void	fill_cmd(t_cmd *node, t_list **tokens, t_process *proc)
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
			if (*tokens)
			{
				parse_redir(node, str, (char *)(*tokens)->content, proc);
				*tokens = (*tokens)->next;
			}
		}
		else
		{
			node->args[i++] = ft_strdup(str);
			*tokens = (*tokens)->next;
		}
	}
	node->args[i] = NULL;
}

int	ft_tokens_to_cmds(t_process *proc)
{
	t_list	*curr;
	t_cmd	**node_ptr;
	t_cmd	*new;

	curr = proc->tokens;
	proc->commands = NULL;
	node_ptr = &proc->commands;
	while (curr)
	{
		if (((char *)curr->content)[0] == '|')
		{
			curr = curr->next;
			continue ;
		}
		new = ft_new_cmd();
		if (!new)
			return (0);
		new->args = malloc(sizeof(char *) * (count_args(curr) + 1));
		fill_cmd(new, &curr, proc);
		*node_ptr = new;
		node_ptr = &new->next;
	}
	return (1);
}
