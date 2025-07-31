/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:21:54 by aghergut          #+#    #+#             */
/*   Updated: 2025/07/31 21:47:07 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_builtins(t_utils *main_struct, char *envp[])
{
	if (!ft_strncmp(main_struct->tokens[0], "clear", ft_strlen("clear")))
		ft_clear();
	else if (!ft_strncmp(main_struct->tokens[0], "exit", ft_strlen("exit")) \
            && !ft_exit(main_struct))
		return (0);	
	else if (!ft_strncmp(main_struct->tokens[0], "export", ft_strlen("export")) \
            && !ft_export(main_struct, envp))
		return (0);
	else if (!ft_strncmp(main_struct->tokens[0], "pwd", ft_strlen("pwd")) \
            && !ft_pwd(main_struct, NULL))
		return (0);
	else if (!ft_strncmp(main_struct->tokens[0], "env", ft_strlen("env")) \
            && !ft_getenv(envp))
		return (0);	
	else if (!ft_strncmp(main_struct->tokens[0], "echo", ft_strlen("echo")) \
            && !ft_echo(main_struct, envp))
		return (0);
	else if (!ft_strncmp(main_struct->tokens[0], "unset", ft_strlen("unset")) \
            && !ft_unset(main_struct, envp))
		return (0);
	return (1);
}
