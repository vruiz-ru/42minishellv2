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

int	ft_isbuiltin(t_process *process)
{
	char	*cmd;
	int size;

	if (!process->tokens)
		return (0);
	cmd = (char *)process->tokens->content;
	size = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "clear", size) || \
		!ft_strncmp(cmd, "export", size) || \
		!ft_strncmp(cmd, "pwd", size) || \
		!ft_strncmp(cmd, "env", size) || \
		!ft_strncmp(cmd, "echo", size) || \
		!ft_strncmp(cmd, "unset", size) || \
		!ft_strncmp(cmd, "cd", size))
		return (1);
	return (0);
}