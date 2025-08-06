/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getcwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:41:00 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/06 08:24:54 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_pwd(t_subproc *process)
{
	char    *dir_path;
	char	*buff;

	buff = ft_getcwd();
	dir_path = ft_strnstr(buff, process->ptr_main->name, ft_strlen(buff));
	if (!dir_path)
		return (0);
	ft_printf("%s\n", dir_path);
	free(buff);
	return (1);
}