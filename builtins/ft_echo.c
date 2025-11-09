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
*/
int	ft_echo(t_process *process)
{
	char	*res;
	
	res = NULL;
	res = ft_construct(process->tokens, res);
	ft_printf("%s\n",res);
	return (free(res), 1);
}
