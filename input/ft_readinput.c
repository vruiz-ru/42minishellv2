/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readinput.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:35:16 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/03 18:28:38 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	ft_readinput(t_process *process)
{
	process->prompt->display = ft_prompt(process);
	if (process->prompt->display == NULL)
	{
        perror("malloc");
        return ;
    }
    ft_putstr_fd("here in readinput\n", 1);
	process->line = readline(process->prompt->display);
	if (process->line == NULL || *(process->line) == '\0')
		return ;
	add_history(process->line);
	ft_parse_line(process);
}
