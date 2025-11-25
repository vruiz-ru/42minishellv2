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

/* Función auxiliar para actualizar el entorno real */
static void	update_env_str(t_process *proc, char *key, char *value)
{
	char	*full_str;
	int		idx;

	if (!value)
		return ;
	// Construimos la cadena completa (ej: "PWD=/home")
	full_str = ft_strjoin(key, value);
	if (!full_str)
		return ;
	
	// Buscamos si la variable ya existe
	idx = ft_mapitem_index(proc->envs->parent_env, key);
	
	// Si existe la reemplazamos, si no la creamos
	if (idx >= 0)
		ft_mapitem_replace(&proc->envs->parent_env, full_str, idx);
	else
		ft_mapitem_add(&proc->envs->parent_env, full_str);
	
	free(full_str);
}

/* Lógica para 'cd ..' cuando el directorio ha sido borrado */
void	update_logical_parent(t_process *process)
{
	char	*current;
	char	*last_slash;
	char	*new_path;

	current = process->prompt->current_wd;
	if (!current)
		return ;
	last_slash = ft_strrchr(current, '/');
	if (!last_slash || last_slash == current)
	{
		if (ft_strlen(current) > 1)
			new_path = ft_strdup("/");
		else
			return ;
	}
	else
		new_path = ft_substr(current, 0, last_slash - current);
	if (new_path)
	{
		free(process->prompt->current_wd);
		process->prompt->current_wd = new_path;
	}
}

void	ft_setpaths(t_process *process)
{
	char	*physical_cwd;

	// 1. Actualizar la estructura interna (Prompt)
	if (process->prompt->last_wd)
		free(process->prompt->last_wd);
	
	// Guardamos el path actual antes de cambiarlo (será el OLDPWD)
	if (process->prompt->current_wd)
		process->prompt->last_wd = ft_strdup(process->prompt->current_wd);
	else
		process->prompt->last_wd = ft_strdup("");

	physical_cwd = ft_getcwd();
	if (physical_cwd)
	{
		if (process->prompt->current_wd)
			free(process->prompt->current_wd);
		process->prompt->current_wd = physical_cwd;
	}
	// 2. Sincronizar las variables de entorno REALES (Lo nuevo)
	// Actualizamos OLDPWD con el valor antiguo que acabamos de guardar
	update_env_str(process, "OLDPWD=", process->prompt->last_wd);
	
	// Actualizamos PWD con el nuevo valor actual
	update_env_str(process, "PWD=", process->prompt->current_wd);
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
        return (0);
    }
    return (0);
}