/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 11:17:20 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/09 11:17:39 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/* 1. Configura la entrada/salida de los pipes */
/* - Si prev_fd != 0, lee del comando anterior.
      - Si hay cmd->next, escribe en el pipe actual. */
void	config_pipes(t_cmd *cmd, int *pipefd, int prev_fd)
{
	if (prev_fd != 0)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
}

/* 2. Aplica redirecciones de archivo (<, >, >>) */
/* NOTA BASH: Las redirecciones tienen prioridad sobre los pipes.
      Si un comando tiene '>', escribirá en el archivo, no en el pipe. */
/*
	  void	apply_redirections(t_cmd *cmd)
{
	if (cmd->fd_in != 0)
	{
		if (cmd->fd_in < 0)
			exit(1); // El error ya se imprimió en el parser (perror)
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != 1)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
}*/

/* 3. Cierra los FDs en el proceso padre para evitar leaks */
void	close_fds(t_cmd *cmd, int prev_fd)
{
    (void)cmd; // Ya no usamos 'cmd' aquí, solo 'prev_fd'
    
	if (prev_fd != 0)
		close(prev_fd);
        
    // [ELIMINAR] Todo lo referente a cmd->fd_in y cmd->fd_out
	// if (cmd->fd_in != 0)
	// 	close(cmd->fd_in);
	// if (cmd->fd_out != 1)
	// 	close(cmd->fd_out);
}
