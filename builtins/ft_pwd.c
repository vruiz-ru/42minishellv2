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

int ft_pwd(t_process *process, t_cmd *cmd)
{
	char	*dir_path;
	char	*haystack;
	char	*needle;

	(void)cmd;
	haystack = ft_getcwd();
	needle = process->prompt->shell_name;
	if (needle[0] == '.' && needle[1] == '/')
		needle += 1;
	dir_path = ft_strnstr(haystack, needle, ft_strlen(haystack));
	if (!dir_path)
		return (0);
	ft_printf("%s\n", dir_path);
	free(haystack);
	return (1);
}