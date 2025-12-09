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

/* 1. Modifica parse_redir para detectar la marca y pasar 'proc' */
static void	parse_redir(t_cmd *node, char *redir, char *file, t_process *proc)
{
	int	heredoc_fd;
	int	expand;
	int	len;

	if (!ft_strncmp(redir, "<<", 3))
	{
		expand = 1; // Por defecto expandimos
		len = ft_strlen(file);
		if (len > 0 && file[len - 1] == 1) // ¿Tiene la marca mágica?
		{
			expand = 0; // Había comillas -> NO expandir
			file[len - 1] = '\0'; // Borramos la marca
		}
		heredoc_fd = ft_heredoc(file, expand, proc); // <--- NUEVA FIRMA
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
			tokens = tokens->next; // Salta símbolo
			if (tokens) tokens = tokens->next; // Salta archivo
		}
		else
		{
			i++;
			tokens = tokens->next;
		}
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


/* 2. Actualiza fill_cmd para recibir y pasar 'proc' */
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



int	ft_tokens_to_cmds(t_process *process)
{
	t_list	*curr;
	t_cmd	*head;
	t_cmd	*last;
	t_cmd	*new;

	curr = process->tokens;
	head = NULL;
	last = NULL;
	while (curr)
	{
		if (((char *)curr->content)[0] == '|') // Saltamos pipes en la lista
		{
			curr = curr->next;
			continue ;
		}
		new = ft_new_cmd();
		if (!new)
			return (0);
		new->args = malloc(sizeof(char *) * (count_args(curr) + 1));
		fill_cmd(new, &curr, process);
		if (!head)
			head = new;
		else
			last->next = new;
		last = new;
	}
	process->commands = head;
	return (1);
}
