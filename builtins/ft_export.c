/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:51:21 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/03 22:50:25 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	is_valid_id(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	export_logic(t_process *process, char *arg)
{
	char	*name;
	char	*eq_pos;
	int		idx;

	eq_pos = ft_strchr(arg, '=');
	if (eq_pos)
		name = ft_substr(arg, 0, eq_pos - arg);
	else
		name = ft_strdup(arg);
	idx = ft_mapitem_index(process->envs->parent_env, name);
	if (idx >= 0 && eq_pos)
		ft_mapitem_replace(&process->envs->parent_env, arg, idx);
	else if (idx < 0)
		ft_mapitem_add(&process->envs->parent_env, arg);
	free(name);
}

int	ft_export(t_process *process, t_cmd *cmd)
{
	int	i;
	int	status;

	status = 0;
	if (!cmd->args[1])
		return (0);
	i = 1;
	while (cmd->args[i])
	{
		if (!is_valid_id(cmd->args[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			status = 1;
		}
		else
		{
			export_logic(process, cmd->args[i]);
		}
		i++;
	}
	return (status);
}
