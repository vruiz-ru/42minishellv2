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
#include <errno.h>

static void	ft_execute_external(t_process *process, t_cmd *cmd)
{
	char	*path;

	path = ft_get_cmd_path(cmd->args[0], process->envs->parent_env);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	if (execve(path, cmd->args, process->envs->parent_env) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(cmd->args[0]);
		free(path);
		if (errno == EACCES)
			exit(126);
		exit(1);
	}
}

static void	child_process(t_process *proc, t_cmd *cmd, int *pipefd, int prev)
{
	proc->pid = fork();
	if (proc->pid == 0)
	{
		config_pipes(cmd, pipefd, prev);
		apply_redirections(cmd);
		ft_execute_external(proc, cmd);
	}
}

int	ft_fork_process(t_process *process)
{
	t_cmd	*cmd;
	int		pipefd[2];
	int		prev_fd;
	int		status;

	cmd = process->commands;
	prev_fd = 0;
	while (cmd)
	{
		if (cmd->next && pipe(pipefd) == -1)
			return (perror("pipe"), 0);
		child_process(process, cmd, pipefd, prev_fd);
		close_fds(cmd, prev_fd);
		if (cmd->next)
		{
			close(pipefd[1]);
			prev_fd = pipefd[0];
		}
		cmd = cmd->next;
	}
	while (waitpid(-1, &status, 0) > 0)
		;
	if (WIFEXITED(status))
		process->status = WEXITSTATUS(status);
	return (1);
}