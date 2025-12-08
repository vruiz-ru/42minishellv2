/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:41:00 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/02 18:54:50 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(t_process *process, t_cmd *cmd)
{
	char	*cwd;

	(void)cmd;
	if (process->prompt->current_wd)
	{
		ft_printf("%s\n", process->prompt->current_wd);
		return (0);
	}
	cwd = ft_getcwd();
	if (cwd)
	{
		ft_printf("%s\n", cwd);
		free(cwd);
		return (0);
	}
	return (1);
}
