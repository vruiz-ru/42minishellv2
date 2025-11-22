/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 09:55:23 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/02 18:52:12 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

void ft_setpaths(t_process *process)
{
    char    *last_wd;
    char    *current_wd;

    last_wd = process->prompt->last_wd;
    current_wd = process->prompt->current_wd;
    
    if (process->prompt->last_wd)
        free(process->prompt->last_wd);
    process->prompt->last_wd = ft_strdup(current_wd);
    
    if (process->prompt->current_wd)
        free(process->prompt->current_wd);
    process->prompt->current_wd = ft_getcwd();
}

int invalid_options(char *token)
{
    int     idx;
    int     count;
    
    count = 0;
    idx = 0;
    while (token[idx])
    {
        if (count > 2 && idx == count)
            return (1);
        if (token[idx] == '-')
            count++;
        idx++;
    }
    return (0);
} 

// Actualizado para usar cmd->args en vez de tokens
int path_input(t_process *process, t_cmd *cmd)
{
    char    *path;

    // El path está en el argumento 1 (el 0 es "cd")
    if (!cmd->args[1]) 
        return (0);
        
    path = cmd->args[1];
    if (ft_isalnum(path[0]) || path[0] == '.' || path[0] == '/')
    {
        if (cmd->args[2]) // Si hay un tercer argumento (cd ruta algo)
            return (ft_putstr_fd("cd: too many arguments\n", 2), 1);
            
        if (chdir(path) != 0)
        {
            ft_putstr_fd("cd: ", 2);
            ft_putstr_fd(path, 2);
            ft_putstr_fd(": No such file or directory\n", 2);
            return (1);
        }
        ft_setpaths(process);
        return (1);
    }
    return (0);
}