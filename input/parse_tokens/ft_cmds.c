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


static void parse_redir(t_cmd *node, char *redir, char *file)
{
    int heredoc_fd;

    if (!ft_strncmp(redir, "<<", 3))
    {
        // El heredoc es el único que ejecutamos YA para capturar el input
        heredoc_fd = ft_heredoc(file);
        ft_add_io(node, IO_HEREDOC, NULL, heredoc_fd);
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

// Versión final de fill_cmd: Solo parsea argumentos y registra redirecciones
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
			*tokens = (*tokens)->next; // Saltamos el símbolo (<, >>...)
            
			// Saltamos espacios hasta encontrar el archivo
			while (*tokens && !ft_strncmp((*tokens)->content, " ", 2))
				*tokens = (*tokens)->next;
            
			if (*tokens)
                // Registramos la redirección para que la abra el HIJO más tarde
				parse_redir(node, str, (char *)(*tokens)->content);
		}
		else if (ft_strncmp(str, " ", 2) != 0) // Si no es espacio ni redirección
		{
            // Añadimos el argumento tal cual (sin concatenación especial)
			node->args[i++] = ft_strdup(str);
		}
		
		if (*tokens)
			*tokens = (*tokens)->next;
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
		if (!ft_strncmp(curr->content, " ", 2) || \
			((char *)curr->content)[0] == '|')
		{
			curr = curr->next;
			continue ;
		}
		new = ft_new_cmd();
		if (!new)
			return (0);
		new->args = malloc(sizeof(char *) * (count_args(curr) + 1));
		fill_cmd(new, &curr);
		if (!head)
			head = new;
		else
			last->next = new;
		last = new;
	}
	process->commands = head;
	return (1);
}