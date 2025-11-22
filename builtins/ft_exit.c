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

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_process *process, t_cmd *cmd)
{
	int	status;

	ft_putstr_fd("exit\n", 1);
	status = 0;
	if (cmd->args[1])
	{
		if (!is_numeric(cmd->args[1]))
		{
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
			status = 255;
		}
		else if (cmd->args[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
		else
			status = ft_atoi(cmd->args[1]);
	}
	else
		status = process->status;
	free_process(process);
	rl_clear_history();
	exit(status);
	return (1);
}

/*
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
}*/