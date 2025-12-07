/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:49:41 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/09 14:36:41 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include <fcntl.h>

static int  set_infile(char *path, int heredoc_fd, t_io_type type)
{
    int fd;

    if (type == IO_HEREDOC)
    {
        if (heredoc_fd == -1) // Si el heredoc falló en el parser (ej: Ctrl+C)
            return (1);
        fd = heredoc_fd; // Usamos el FD que nos pasó el padre
    }
    else
    {
        fd = open(path, O_RDONLY);
        if (fd < 0)
        {
            perror(path); // Bash imprime el error exacto aquí
            return (1);
        }
    }
    dup2(fd, STDIN_FILENO);
    if (type != IO_HEREDOC) // No cerramos heredoc_fd si queremos reusarlo (aunque un dup suele bastar)
        close(fd);
    return (0);
}

static int  set_outfile(char *path, t_io_type type)
{
    int fd;
    int flags;

    if (type == IO_APPEND)
        flags = O_WRONLY | O_CREAT | O_APPEND;
    else
        flags = O_WRONLY | O_CREAT | O_TRUNC;
    
    fd = open(path, flags, 0644);
    if (fd < 0)
    {
        perror(path);
        return (1);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    return (0);
}

// Función principal que llama el hijo
int ft_apply_redirs(t_cmd *cmd)
{
    t_list  *curr;
    t_io    *io;

    curr = cmd->redirs;
    while (curr)
    {
        io = (t_io *)curr->content;
        if (io->type == IO_IN || io->type == IO_HEREDOC)
        {
            if (set_infile(io->path, io->fd, io->type))
                return (1); // Error
        }
        else if (io->type == IO_OUT || io->type == IO_APPEND)
        {
            if (set_outfile(io->path, io->type))
                return (1); // Error
        }
        curr = curr->next;
    }
    return (0); // Éxito
}