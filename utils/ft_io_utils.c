/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_io_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 11:32:12 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/09 14:31:04 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_io	*ft_new_io(t_io_type type, char *path, int fd)
{
	t_io	*new_io;

	new_io = malloc(sizeof(t_io));
	if (!new_io)
		return (NULL);
	new_io->type = type;
	new_io->path = ft_strdup(path);
	new_io->fd = fd;
	if (!new_io->path)
	{
		free(new_io);
		return (NULL);
	}
	return (new_io);
}

void	ft_add_io(t_cmd *cmd, t_io_type type, char *path, int fd)
{
	t_io	*io_node;
	t_list	*new_node;

	io_node = ft_new_io(type, path, fd);
	if (!io_node)
		return ;
	new_node = ft_lstnew(io_node);
	if (!new_node)
	{
		free(io_node->path);
		free(io_node);
		return ;
	}
	ft_lstadd_back(&cmd->redirs, new_node);
}
