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
#include "../builtins/builtins.h"
#include <errno.h>
#include <sys/stat.h>

/* 1. Ejecuta comando externo */
static void	ft_execute_external(t_process *process, t_cmd *cmd)
{
	char	*path;
	struct stat sb; // [NUEVO] Estructura para chequear si es directorio

	path = ft_get_cmd_path(cmd->args[0], process->envs->parent_env);
	if (!path)
	
		cmd_not_found(cmd->args[0]);
	if (execve(path, cmd->args, process->envs->parent_env) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		// Verificamos explícitamente si es un directorio
        if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
        {
            ft_putstr_fd(cmd->args[0], 2);
            ft_putstr_fd(": Is a directory\n", 2);
            free(path);
            exit(126);
        }
		perror(cmd->args[0]);
		free(path);
		if (errno == EACCES)
			exit(126);
		exit(1);
	}
}
/* 2. Lógica del proceso hijo */
static void child_process(t_process *proc, t_cmd *cmd, int *pipefd, int prev)
{
    proc->pid = fork();
    if (proc->pid == 0)
    {
        // 1. RESTAURAR SEÑALES ORIGINALES
        // Queremos que 'cat' muera con Ctrl+C (SIG_DFL = Default)
        signal(SIGINT, SIG_DFL); 
        // Queremos que 'cat' pueda generar core dump con Ctrl+\ (SIG_DFL)
        signal(SIGQUIT, SIG_DFL);

        config_pipes(cmd, pipefd, prev);
        apply_redirections(cmd);
        int ret = ft_builtins(proc, cmd);
		if (ret != -1) // Si era un builtin (retorno != -1)
    		exit(ret); // Salimos con SU código (0 o 1), no con 0 inventado
        ft_execute_external(proc, cmd);
    }
}
/* 3. Espera a los hijos y gestiona señales (Nueva función extraída) */
//Modifica la firma de wait_children para recibir el last_pid
static void	wait_children(t_process *process, int last_pid)
{
	int	status;

	// Esperamos específicamente al último comando para coger SU status
    waitpid(last_pid, &status, 0);
	// Guardamos ese status (es el que importa para $?)
	if (WIFEXITED(status))
		process->status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			write(1, "\n", 1);
			process->status = 130;
		}
		else if (WTERMSIG(status) == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", 1);
			process->status = 131;
		}
		else
			process->status = 128 + WTERMSIG(status);
	}
	// Ahora esperamos al resto de zombis (los otros comandos del pipe)
    while (wait(NULL) > 0);
}

/* 4. Bucle principal */
int	ft_fork_process(t_process *process)
{
	t_cmd	*cmd;
	int		pipefd[2];
	int		prev_fd;
	pid_t last_pid = 0; // [NUEVO] Variable para guardar el PID

	cmd = process->commands;
	prev_fd = 0;
	signal(SIGINT, SIG_IGN);
	while (cmd)
	{
		if (cmd->next && pipe(pipefd) == -1)
			return (perror("pipe"), 0);
		child_process(process, cmd, pipefd, prev_fd);
		last_pid = process->pid; // [NUEVO] Actualizamos en cada vuelta. Al final quedará el último.
		close_fds(cmd, prev_fd);
		if (cmd->next)
		{
			close(pipefd[1]);
			prev_fd = pipefd[0];
		}
		cmd = cmd->next;
	}
	if (prev_fd != 0)
    	close(prev_fd);
	wait_children(process, last_pid);
	signal(SIGINT, ft_sigint);
	return (1);
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
