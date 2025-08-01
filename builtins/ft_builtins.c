/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:21:54 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/01 18:02:11 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_builtins(t_utils *shell, char *envp[])
{
	char    *cmd;

	cmd = (char *)shell->builtins->tokens->content;
	if (!ft_strncmp(cmd, "clear", ft_strlen(cmd)))
		ft_clear();
	else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)) && !ft_exit(shell))
		return (0);	
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)) && \
			!ft_export(shell, envp))
		return (0);
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)) && !ft_pwd(shell))
		return (0);
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd)) && !ft_getenv(envp))
		return (0);	
	else if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)) \
			&& !ft_echo(shell, envp))
		return (0);
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)) \
			&& !ft_unset(shell, envp))
		return (0);
	return (1);
}
