/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inputvar_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:23:06 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/03 18:44:29 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../input.h"

int add_variable(char ***map, char *item)
{
    size_t idx;

    if (!item)
        return (0);
    if (already_exists(*map, item))
    {
        idx = ft_mapitem_index(*map, item);
        if (!ft_mapitem_replace(map, item, idx))
            return (0);
    }
    if (!ft_mapitem_add(map, item))
        return (0);
    return (1);
}

int	contains_variable(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
		i++;
	if (line[i] == '=')
		return (1);
	return (0);
}

int special_variable(t_process *proc, char **var_name, char ch)
{
	proc->is_special = false;
	if (ch == '$')
		*var_name = ft_itoa(proc->pid);
	else if (ch == '?')
		*var_name = ft_itoa(proc->exit_status);
	else if (ch == '0')
		*var_name = ft_strdup(proc->prompt->home_path);
	else if (ch == '_')
		*var_name = ft_strdup(proc->last_arg);
	if (ft_strchr("$?0_", ch) && !*var_name)
		return (perror("malloc"), exit(EXIT_FAILURE), 0);
	if (*var_name)
	{
		proc->is_special = true;
		return (1);
	}
	return (0);
}