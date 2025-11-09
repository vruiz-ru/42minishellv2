/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specialvars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 17:04:00 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/09 18:19:32 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../input.h"

int ft_specialvars(t_process *proc, char **var_name, char ch)
{
	proc->is_special = false;
	if (ch == '$')
		*var_name = ft_itoa(proc->pid);
	else if (ch == '?')
		*var_name = ft_itoa(proc->status);
	else if (ch == '0')
		*var_name = ft_strdup(proc->prompt->home_path);
	if (ft_strchr("$?0_", ch) && !*var_name)
		return (perror("malloc"), exit(EXIT_FAILURE), 0);
	if (*var_name)
	{
		proc->is_special = true;
		return (1);
	}
	return (0);
}