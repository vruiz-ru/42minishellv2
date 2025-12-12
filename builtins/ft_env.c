/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:51:08 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/02 18:55:14 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_env(t_process *process, t_cmd *cmd)
{
	char	**ptr;

	(void)cmd;
	if (!process || !process->envs->parent_env || !*process->envs->parent_env)
		return (0);
	ptr = process->envs->parent_env;
	while (*ptr)
	{
		if (ft_strchr(*ptr, '='))
			ft_printf("%s\n", *ptr);
		ptr++;
	}
	return (0);
}
