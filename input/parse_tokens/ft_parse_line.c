/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 22:07:38 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/03 20:52:37 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../input.h"

int	ft_parse_line(t_process *process)
{
	char	*cmd;
	char    *ptr_line;

	if (contains_variable(process->line))
	{
        ft_putstr_fd("here in parse line1\n", 1);
		if (!ft_inputvar(process, &process->line))
			return (0);
        ft_putstr_fd("here in parse line2\n", 1);
	}
	ptr_line = process->line;
	cmd = ft_strtok(ptr_line, " ");
	ft_safeadd_tokens(&process->tokens, &cmd);
	if (!ft_strchr(ptr_line, ' '))
		return (1);
	if (!ft_std(process, ptr_line) && !ft_quote(process, ptr_line))
		return (0);
	return (1);
}
