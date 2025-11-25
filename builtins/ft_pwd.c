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
	(void)cmd;

	// ESTRATEGIA BASH (Lógica):
	// Si tenemos una ruta guardada en nuestra estructura, la usamos.
	// Esto permite que 'pwd' funcione incluso si el directorio ha sido borrado.
	if (process->prompt->current_wd)
	{
		ft_printf("%s\n", process->prompt->current_wd);
		return (0);
	}
	
	// FALLBACK (Física):
	// Solo si por algún motivo extraño no tenemos ruta guardada, preguntamos al sistema.
	char *cwd = ft_getcwd();
	if (cwd)
	{
		ft_printf("%s\n", cwd);
		free(cwd);
		return (0);
	}
	
	return (1);
}
/*
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
	return (0);
}*/