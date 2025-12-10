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

#include "../builtins/builtins.h"
#include "../headers/minishell.h"
#include <errno.h>
#include <sys/stat.h>

static void	ft_execute_external(t_process *process, t_cmd *cmd)
{
	char	*path;
	int		err;

	path = ft_get_cmd_path(cmd->args[0], process->envs->parent_env);
	if (!path)
		cmd_not_found(cmd->args[0]);
	execve(path, cmd->args, process->envs->parent_env);
	err = errno;
	ft_exec_error(path, cmd->args[0], err);
}

static void	child_process(t_process *proc, t_cmd *cmd, int *pipefd, int prev)
{
	int	ret;

	proc->pid = fork();
	if (proc->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		config_pipes(cmd, pipefd, prev);
		if (ft_apply_redirs(cmd) != 0)
			exit(1);
		ret = ft_builtins(proc, cmd);
		if (ret != -1)
			exit(ret);
		ft_execute_external(proc, cmd);
	}
}

static void	wait_children(t_process *process, int last_pid)
{
	int	status;

	waitpid(last_pid, &status, 0);
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
	while (wait(NULL) > 0)
		;
}

static void	update_parent_fds(t_cmd *cmd, int *pipefd, int *prev_fd)
{
	close_fds(cmd, *prev_fd);
	if (cmd->next)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
}

int	ft_fork_process(t_process *process)
{
	t_cmd	*cmd;
	int		pipefd[2];
	int		prev_fd;
	pid_t	last_pid;

	cmd = process->commands;
	prev_fd = 0;
	last_pid = 0;
	signal(SIGINT, SIG_IGN);
	while (cmd)
	{
		if (cmd->next && pipe(pipefd) == -1)
			return (perror("pipe"), 0);
		child_process(process, cmd, pipefd, prev_fd);
		last_pid = process->pid;
		update_parent_fds(cmd, pipefd, &prev_fd);
		cmd = cmd->next;
	}
	if (prev_fd != 0)
		close(prev_fd);
	wait_children(process, last_pid);
	signal(SIGINT, ft_sigint);
	return (1);
}
