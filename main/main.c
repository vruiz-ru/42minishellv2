/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 11:50:39 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/09 19:37:48 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int		g_signal_status = 0;

void	reset_utils(t_process **process)
{
	if ((*process)->line)
		free((*process)->line);
	ft_clear_strtok();
	if ((*process)->tokens)
		ft_lstclear(&(*process)->tokens, free);
	(*process)->tokens = NULL;
	if ((*process)->commands)
	{
		ft_free_cmds((*process)->commands);
		(*process)->commands = NULL;
	}
	if ((*process)->prompt->display)
		free((*process)->prompt->display);
	(*process)->prompt->display = NULL;
}

static void	execute_commands(t_process *process)
{
	ft_tokens_to_cmds(process);
	if (g_signal_status == 130)
	{
		process->status = 130;
		g_signal_status = 0;
	}
	else if (process->commands && !process->commands->next && \
		ft_is_parent_builtin(process->commands))
	{
		process->status = ft_builtins(process, process->commands);
	}
	else
		ft_fork_process(process);
}

static void	shell_loop(t_process *process)
{
	while (1)
	{
		signal(SIGINT, ft_sigint);
		signal(SIGQUIT, SIG_IGN);
		ft_readinput(process);
		if (g_signal_status != 0)
		{
			process->status = g_signal_status;
			g_signal_status = 0;
		}
		if (process->tokens)
			execute_commands(process);
		reset_utils(&process);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_process	*process;

	if (argc > 1)
		return (0);
	process = NULL;
	if (!init_parent(&process, argv[0], envp))
		return (0);
	shell_loop(process);
	return (0);
}
