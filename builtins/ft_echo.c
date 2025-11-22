/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:59:40 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/09 16:55:38 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
/*

*   treat the flag -n properly -> deletes the \n char *not applied on the double command case*
				*   doesn't recognize simple backslash
						ex: echo \new -> new
							echo \\new -> \new
				*   expect a closing " if there is one
						ex: 1.echo sadas" -> > (for continuation and after we put " will outputs) in this case: 	sadas
																												: command not found
							2. echo "
							> asdsa
							> asdasdsa
							> adsadsa
							> adasdsadsa
							> adsadas
							> "
					[OUTPUT]\n (because the " is on the line with echo and its empty)
							asdsa
							asdasdsa
							adsadsa
							adasdsadsa
							adsadas
							\n (becaue the closing " its on the last row and its empty)
				*	treat the variable within '$VAR' literally, 
				*	instead of "$VAR" or $VAR which prints the value of that specific variable (in case of variable doesn't exists, will print a new line char)
		!!!!		other example with {} special char
						$> foo=4
						$> echo $foo
						4
						$> echo ${foo}d
						4d
				*	echo $? will print the exit status of the last executed cmd
				.----------------------------------------------.
				| $$ - print parent process id with getppid(); |
				'----------------------------------------------'
				the differences between getpid and getppid:
					getpid returns the id of the current instance execution
					get ppid returns the id of the whole process of file we are working on

int	ft_echo(t_process *process)
{
	char	*res;
	
	res = NULL;
	res = ft_construct(process->tokens, res);
	ft_printf("%s\n",res);
	return (free(res), 1);
}*/

// Función auxiliar para imprimir el array de argumentos
static void print_args(char **args, int i)
{
    while (args[i])
    {
        ft_putstr_fd(args[i], 1);
        if (args[i + 1]) // Si hay más argumentos, imprime espacio
            write(1, " ", 1);
        i++;
    }
}

// Detecta si el flag es válido (ej: -n, -nnnn, pero no -n-n o -na)
static int is_n_flag(char *arg)
{
    int i;

    if (!arg || ft_strncmp(arg, "-n", 2) != 0)
        return (0);
    i = 2;
    while (arg[i])
    {
        if (arg[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

int ft_echo(t_process *process, t_cmd *cmd)
{
    int i;
    int n_option;

    (void)process; // No lo necesitamos en echo
    i = 1;
    n_option = 0;
    
    // Saltamos todos los flags -n válidos consecutivos (echo -n -n -n hola)
    while (cmd->args[i] && is_n_flag(cmd->args[i]))
    {
        n_option = 1;
        i++;
    }
    
    print_args(cmd->args, i);
    
    if (!n_option)
        write(1, "\n", 1);
        
    return (1); // Retornamos 1 para decir "ejecutado con éxito"
}