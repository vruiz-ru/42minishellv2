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

#include "input.h"

extern int	g_signal_status;

void	ft_readinput(t_process *process)
{
	process->prompt->display = ft_prompt(process);
	if (process->prompt->display == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	process->line = readline(process->prompt->display);
	if (g_signal_status != 0)
	{
		process->status = g_signal_status;
		g_signal_status = 0;
	}
	if (process->line == NULL)
	{
		ft_putstr_fd("exit\n", 1);
		exit(process->status);
	}
	if (*(process->line) == '\0')
		return ;
	add_history(process->line);
	ft_parse_line(process);
}
