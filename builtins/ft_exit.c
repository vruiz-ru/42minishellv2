/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:50:12 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/09 17:56:39 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_exit(t_process *process)
{
	char    *cmd;

	cmd = NULL;
	if (process->tokens)
		cmd = (char *)process->tokens->content;
	else
		return (0);
	if (ft_strncmp(cmd, "exit", ft_strlen(cmd)))
		return (0);
	free_process(process);
	rl_clear_history();
	ft_putstr_fd("exit\n", 1);
	exit(EXIT_SUCCESS);
	return (1);
}