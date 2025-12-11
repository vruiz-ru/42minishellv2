/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 20:06:37 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/02 18:56:52 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	ft_home(t_process *process)
{
	char	*home_path;

	home_path = ft_getvar(process->envs->parent_env, "HOME");
	if (!home_path)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	if (chdir(home_path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(home_path);
		free(home_path);
		return (1);
	}
	ft_setpaths(process);
	free(home_path);
	return (0);
}

int	ft_cd(t_process *process, t_cmd *cmd)
{
	char	*arg;

	if (!cmd->args[1])
		return (ft_home(process));
	arg = cmd->args[1];
	if (invalid_options(arg))
		return (ft_putstr_fd("cd: invalid options\n", 2), 1);
	if (!ft_strncmp(arg, "..", 3))
		return (up_feature(process, cmd));
	if (arg[0] == '~')
		return (home_feature(process, cmd));
	if (!ft_strncmp(arg, "-", 2) && !arg[1])
		return (back_feature(process, cmd));
	if (!ft_strncmp(arg, "--", 3))
		return (dash_feature(process, cmd));
	return (path_input(process, cmd));
}
