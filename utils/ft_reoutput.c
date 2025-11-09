/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reoutput.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:48:19 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/05 22:16:36 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/* 	">"
	Redirects the standard output (stdout) of a command to the file given by WORD
	If the file does not exist, it is created.
	If the file exists, it is truncated to zero length (erased) before the command is executed

	Edge cases:
	*	If the command fails to start (e.g., a typo), 
		the file is still truncated to zero bytes as soon as the shell parses the redirection.
			
		>:$ echo "keepme" >test.txt
		>:$ cat test.txt
		keepme
		>:$ notacommand >test.txt
		>:$ cat test.txt
		(empty)
	*	If the user does not have write permission for the target file, 
		the shell will throw a "Permission denied" error, and the command will not run.	
	*	If the target is a directory, the shell will report "Is a directory" and not run the command.
	*	If the same stream is redirected more than once, only the last one takes effect
		
		>:$ echo test >a >b
			# Only 'b' gets the output
			# Will create both a & b file
*/

int	ft_reoutput(t_process *process)
{
	(void)process;
	return (0);	
}