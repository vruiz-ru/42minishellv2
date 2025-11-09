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
}
