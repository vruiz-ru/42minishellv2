/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readinput.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:35:16 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/09 14:38:10 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "input.h"

void	ft_readinput(t_process *process)
{
	int	exit_code;

	process->prompt->display = ft_prompt(process);
	process->line = readline(process->prompt->display);
	if (g_signal_status != 0)
	{
		process->status = g_signal_status;
		g_signal_status = 0;
	}
	if (process->line == NULL)
	{
		ft_putstr_fd("exit\n", 1);
		exit_code = process->status;
		free_process(process);
		rl_clear_history();
		exit(exit_code);
	}
	if (*(process->line) == '\0')
		return ;
	add_history(process->line);
	ft_parse_line(process);
}
