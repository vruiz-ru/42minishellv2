/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:49:41 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/09 14:36:41 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
 
#include "../headers/minishell.h"

// Libera la memoria de un array de strings (útil para limpiar tras ft_split)
void ft_free_array(char **arr)
{
    int i = 0;
    if (!arr) return;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

// Busca el binario ejecutable en las rutas del PATH
char *ft_get_cmd_path(char *cmd, char **envp)
{
    char    **paths;
    char    *path_part;
    char    *exec_path;
    int     i;

    // 1. Si el comando ya es una ruta (empieza por / o ./), no buscamos
    if (ft_strchr(cmd, '/') != NULL)
    {
        if (access(cmd, F_OK) == 0)
            return (ft_strdup(cmd));
        return (NULL); // No existe
    }

    // 2. Buscar la variable "PATH=" en el entorno
    i = 0;
    while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
        i++;
    if (!envp[i]) return (NULL); // No hay PATH definido

    // 3. Separar las rutas por ':' (PATH=/bin:/usr/bin:etc)
    paths = ft_split(envp[i] + 5, ':');
    
    // 4. Probar ruta por ruta
    i = -1;
    while (paths[++i])
    {
        // Construimos: ruta + "/" + comando
        path_part = ft_strjoin(paths[i], "/");
        exec_path = ft_strjoin(path_part, cmd);
        free(path_part);

        // ¿Existe y es ejecutable?
        if (access(exec_path, F_OK | X_OK) == 0)
        {
            ft_free_array(paths);
            return (exec_path); // ¡Lo encontramos!
        }
        free(exec_path);
    }
    ft_free_array(paths);
    return (NULL); // No lo encontramos
}

/* Función para imprimir error completo de una sola vez y salir */
void	cmd_not_found(char *cmd)
{
	char	*msg;
	char	*tmp;

	// Construimos: "minishell: " + cmd + ": command not found\n"
	tmp = ft_strjoin("minishell: ", cmd);
	msg = ft_strjoin(tmp, ": command not found\n");
	free(tmp);
	
	// Escribimos todo junto (Atómico)
	ft_putstr_fd(msg, 2);
	free(msg);
	exit(127);
}