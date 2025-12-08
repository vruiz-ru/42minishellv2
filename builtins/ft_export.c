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

static void	print_export_line(char *str)
{
	char	*eq;

	if (ft_strncmp(str, "_=", 2) == 0)
		return ;
	ft_putstr_fd("declare -x ", 1);
	eq = ft_strchr(str, '=');
	if (eq)
	{
		write(1, str, eq - str);
		write(1, "=\"", 2);
		ft_putstr_fd(eq + 1, 1);
		write(1, "\"\n", 2);
	}
	else
	{
		ft_putstr_fd(str, 1);
		write(1, "\n", 1);
	}
}

static int	export_no_args(t_process *p)
{
	char	**dup;
	char	*tmp;
	int		i;
	int		j;

	dup = ft_mapdup(p->envs->parent_env);
	if (!dup)
		return (1);
	i = -1;
	while (dup[++i])
	{
		j = -1;
		while (dup[++j + 1])
		{
			if (ft_strncmp(dup[j], dup[j + 1], ft_strlen(dup[j]) + 1) < 0)
			{
				tmp = dup[j];
				dup[j] = dup[j + 1];
				dup[j + 1] = tmp;
			}
		}
	}
	while (i-- > 0)
		print_export_line(dup[i]);
	return (ft_mapfree(&dup), 0);
}

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
		return (export_no_args(process));
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
			export_logic(process, cmd->args[i]);
		i++;
	}
	return (status);
}
