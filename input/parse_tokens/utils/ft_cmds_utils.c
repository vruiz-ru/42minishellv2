/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:49:41 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/09 14:36:41 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
#include <fcntl.h>

t_cmd	*ft_new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->path = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

/* Detecta si es cualquier redirección */
int	is_redir(char *str)
{
	if (!ft_strncmp(str, "<<", 3)) // << (len 2 + null)
		return (1);
	if (!ft_strncmp(str, ">>", 3)) // >>
		return (1);
	if (!ft_strncmp(str, "<", 2))  // <
		return (1);
	if (!ft_strncmp(str, ">", 2))  // >
		return (1);
	return (0);
}
/*
 Abre el archivo correspondiente o lanza el heredoc 
void	open_file(t_cmd *cmd, char *symbol, char *file)
{
    // CASO HEREDOC (<<)
	if (!ft_strncmp(symbol, "<<", 3))
	{
		if (cmd->fd_in != 0)
			close(cmd->fd_in);
		cmd->fd_in = ft_heredoc(file); // 'file' aquí es el delimitador
	}
    // CASO INPUT (<)
	else if (!ft_strncmp(symbol, "<", 2))
	{
		if (cmd->fd_in != 0)
			close(cmd->fd_in);
		cmd->fd_in = open(file, O_RDONLY);
		if (cmd->fd_in < 0)
			perror(file);
	}
    // CASOS OUTPUT (>, >>)
	else
	{
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
		if (!ft_strncmp(symbol, ">", 2))
			cmd->fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			cmd->fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
}*/
