/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:59:40 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/09 16:55:38 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	print_args(char **args, int i)
{
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
}

static int	is_n_flag(char *arg)
{
	int	i;

	if (!arg || ft_strncmp(arg, "-n", 2) != 0)
		return (0);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_process *process, t_cmd *cmd)
{
	int	i;
	int	n_option;

	(void)process;
	i = 1;
	n_option = 0;
	while (cmd->args[i] && is_n_flag(cmd->args[i]))
	{
		n_option = 1;
		i++;
	}
	print_args(cmd->args, i);
	if (!n_option)
		write(1, "\n", 1);
	return (0);
}
