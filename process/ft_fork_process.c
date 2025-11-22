/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 10:36:15 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/09 17:01:30 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/* mini/process/ft_pipe_utils.c */
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
}

/* 3. Cierra los FDs en el proceso padre para evitar leaks */
void	close_fds(t_cmd *cmd, int prev_fd)
{
	if (prev_fd != 0)
		close(prev_fd);
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	if (cmd->fd_out != 1)
		close(cmd->fd_out);
}


/*
int	ft_fork_process(t_process *process, int(*built_f)(t_process *))
{
	int	status;

	if (!ft_isbuiltin(process))
		return (0);
	process->pid = fork();
	if (process->pid < 0)
		return (perror("fork"), exit(EXIT_FAILURE), 0);
	if (process->pid == 0)
	{
		if (built_f(process))
			exit(EXIT_SUCCESS);
		exit(EXIT_FAILURE);
	}
	if (waitpid(process->pid, &status, 0) < 0)
		return (perror("waitpid"), exit(EXIT_FAILURE), 0);
	if (WIFEXITED(status))
		process->status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		process->status = 128 + WTERMSIG(status);
	else if (WIFSIGNALED(status))
		process->status = 128 + WIFSTOPPED(status);
	return(1);
}*/
