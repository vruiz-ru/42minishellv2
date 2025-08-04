/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reinput.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:43:35 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/04 14:38:58 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* "<" 
Reads input for a command from a file instead of stdin.

Edge Cases:

	File exists but is empty: Command receives no input and may block or fail (e.g., cat < emptyfile gives no output).

	File does not exist: The shell prints an error (e.g., cat < nonexist → "No such file or directory") and the command is not run.

	Read permissions: If you lack read permission, you'll get a "Permission denied" error.

	Multiple redirections: Only the last input redirection takes effect in most shells: cat <file1 <file2 reads from file2.

	Used with built-ins: Some built-ins (like read) behave differently when input is redirected (e.g., read var < file reads the first line from file, not from stdin).

	Truncation side effect: Unlike output redirection, input redirection < never alters the input file.

*/

int	ft_reinput(t_subproc *process)
{
	(void)process;
	return (0);
}