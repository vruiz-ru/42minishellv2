/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:51:21 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/10 11:23:22 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_transfer(t_subproc *process, char *var)
{
	char	*get_var;
	int		idx;

	idx = ft_mapitem_index(process->buffer_env, var);
	if (idx < 0)
		return (0);
	get_var = ft_strdup(process->buffer_env[idx]);
	if (!get_var)
		return (0);
	if (!ft_mapitem_del(&process->buffer_env, idx))
		return (free(get_var), 0);
	if (!ft_mapitem_add(&process->local_env, get_var))
		return (free(get_var), 0);
	return (1);
}

static int	check_update(char **map, char *var)
{
	int 	env_idx;
	
	env_idx = ft_mapitem_index(map, var);
	if (env_idx < 0)
		return (0);
	if (!ft_mapitem_replace(&map, var, env_idx))
		return (0);
	return (1);
}

int ft_export(t_subproc *process)
{
	char	*line;
	bool	done;

	ft_clear_strtok();
	line = ft_construct_line(process->builtins->tokens);
	done = false;
	if (check_update(process->local_env, line))
		done = true;
	if (done == false && check_transfer(process, line))
		done = true;
	if (done == false && !ft_mapitem_add(&process->local_env, line))
		return (0);
	return (free(line), 1);
}
