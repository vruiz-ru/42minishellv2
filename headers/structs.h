/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:11:10 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/09 13:52:02 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#include "../import/libft/lists/lists.h"
#include <stdbool.h>

typedef struct	Environment_utils
{
	char	**parent_env;
	char	**static_env;
}	t_envs;

typedef struct	Prompt_utils
{
	char	*display;
	char	*shell_name;
	char	*home_path;
	char	*current_wd;
	char	*last_wd;
}	t_prompt;

// Tipos de redirección
typedef enum e_io_type
{
    IO_IN,      // <
    IO_OUT,     // >
    IO_APPEND,  // >>
    IO_HEREDOC  // <<
}   t_io_type;

//Estructura para almacenar UNA redirección pendiente
typedef struct s_io
{
    t_io_type   type;
    char        *path; // Nombre del archivo
    int         fd;    // Solo se usa para guardar el FD del heredoc (que ya está abierto)
}   t_io;


typedef struct s_cmd
{
    char            **args;       // El comando y sus flags listos para execve. Ej: {"ls", "-la", NULL}
    char            *path;        // La ruta absoluta del binario. Ej: "/bin/ls"
	t_list          *redirs; // [NUEVO] Lista de (t_io *)
   // int             fd_in;        // De dónde lee (0 por defecto, o un archivo '<', o un pipe)
   // int             fd_out;       // Dónde escribe (1 por defecto, o un archivo '>', o un pipe)
    struct s_cmd    *next;        // Puntero al siguiente comando (si hay un pipe '|')
} t_cmd;

typedef struct Process_utils
{
    t_prompt    *prompt;
    t_envs      *envs;
    t_list      *tokens;    // Tu lista original (Lexer)
    t_cmd       *commands;  // <--- ¡NUEVO! Tu lista estructurada (Parser)
    pid_t       pid;
    char        *line;
    int         status;
    int         forks;
    bool        is_special;
    bool        is_variable;
	bool        in_heredoc;
}   t_process;

#endif