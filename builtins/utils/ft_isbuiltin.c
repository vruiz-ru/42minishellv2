/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isbuiltin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 16:51:07 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/09 16:55:02 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

/* Comprueba si es CUALQUIER builtin (para el hijo) */
int	ft_isbuiltin(t_cmd *cmd)
{
	char	*p;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	p = cmd->args[0];
	if (!ft_strncmp(p, "echo", 5) || !ft_strncmp(p, "cd", 3) || \
		!ft_strncmp(p, "pwd", 4) || !ft_strncmp(p, "export", 7) || \
		!ft_strncmp(p, "unset", 6) || !ft_strncmp(p, "env", 4) || \
		!ft_strncmp(p, "exit", 5) || !ft_strncmp(p, "clear", 6))
		return (1);
	return (0);
}

/* Comprueba si es un builtin que debe correr en el PADRE (para persistir) */
int	ft_is_parent_builtin(t_cmd *cmd)
{
	char	*p;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	p = cmd->args[0];
	// Solo estos modifican el entorno o el estado del shell padre
	if (!ft_strncmp(p, "cd", 3) || !ft_strncmp(p, "export", 7) || \
		!ft_strncmp(p, "unset", 6) || !ft_strncmp(p, "exit", 5))
		return (1);
	return (0);
}