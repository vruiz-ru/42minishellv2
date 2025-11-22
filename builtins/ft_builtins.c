/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:21:54 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/09 16:50:44 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int ft_builtins(t_process *process, t_cmd *cmd)
{
    char *program;
    int  len;

    if (!cmd || !cmd->args || !cmd->args[0])
        return (0);
    
    program = cmd->args[0];
    len = ft_strlen(program);

    // Comparamos con strncmp asegurando que la longitud coincide
    if (!ft_strncmp(program, "echo", len) && len == 4)
        return (ft_echo(process, cmd));
    if (!ft_strncmp(program, "cd", len) && len == 2)
        return (ft_cd(process, cmd));
    if (!ft_strncmp(program, "pwd", len) && len == 3)
        return (ft_pwd(process, cmd));
    if (!ft_strncmp(program, "export", len) && len == 6)
        return (ft_export(process, cmd));
    if (!ft_strncmp(program, "unset", len) && len == 5)
        return (ft_unset(process, cmd));
    if (!ft_strncmp(program, "env", len) && len == 3)
        return (ft_env(process, cmd));
    if (!ft_strncmp(program, "exit", len) && len == 4)
        return (ft_exit(process, cmd));
    if (!ft_strncmp(program, "clear", len) && len == 5)
        return (ft_clear(process, cmd));
        
    return (0); // No era un builtin
}
