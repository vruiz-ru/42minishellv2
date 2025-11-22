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

static void	update(char ***map, char *var)
{
	int 	env_idx;
	
	env_idx = ft_mapitem_index(*map, var);
	if (env_idx < 0)
		return ;
	if (!ft_mapitem_replace(map, var, env_idx))
		return ;
	return ;
}

static void	transfer(t_process *process, char *var)
{
	char	*get_var;
	int		idx;
	
	idx = ft_mapitem_index(process->envs->static_env, var);
	if (idx < 0)
		return ;
	get_var = ft_strdup(process->envs->static_env[idx]);
	if (!get_var)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	if (ft_mapitem_index(process->envs->parent_env, get_var) < 0 && \
		!ft_mapitem_add(&process->envs->parent_env, get_var))
	{
		free(get_var);
		return ;
	}
	ft_mapitem_del(&process->envs->static_env, idx);
	free(get_var);
	return ;
}

int ft_export(t_process *process, t_cmd *cmd)
{
	char	**local;
	char	*line;
	int		idx;

	(void)cmd;
	local = process->envs->static_env;
	line = ft_construct(process->tokens, NULL);
	idx = ft_mapitem_index(local, line);
	if (!ft_strchr(line, '='))
	{
		if (idx < 0)
			return (1);
		if (ft_mapitem_index(process->envs->parent_env, local[idx]) < 0)
		{
			if (!ft_mapitem_add(&process->envs->parent_env, local[idx]))
				return (perror("malloc"), exit(EXIT_FAILURE), free(line), 0);
		}
		return (free(line), 1);
	}
	update(&process->envs->parent_env, line);
	update(&process->envs->static_env, line);
	if (ft_mapitem_index(process->envs->parent_env, line) < 0 && idx < 0 && \
		!ft_mapitem_add(&process->envs->parent_env, line))
		return (perror("malloc"), exit(EXIT_FAILURE), free(line), 0);
	transfer(process, line);
	return (free(line), 1);
}
