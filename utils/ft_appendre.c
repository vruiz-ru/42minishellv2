/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_appendre.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:38:52 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/04 22:30:38 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* ">>" 
Appends stdout to a file, instead of overwriting.

Edge Cases:

I. File doesn't exist: The shell creates the file.
	>:$ echo "Hello" >> newfile.txt
		* If newfile.txt does not exist, the shell creates it.
		* Output is appended (since file is new, it just writes that text).
		
II.	Permissions: No write permission causes failure.
	>:$ mkdir /root/protected_dir
	>:$ chmod 555 /root/protected_dir
	>:$ echo "test" >> /root/protected_dir/file.txt
		* Attempting to append to a file in a directory without write permissions for your user fails with a permission error.
		* The file is not created or modified.

III.Delayed creation: File is created at parsing time, not after command execution.
	>:$ echo "start" >> fileA >> fileB		
		* Both fileA and fileB are created immediately during parsing, even before echo executes.
		* Output goes only to fileB (the last redirection overrides previous).
		* fileA exists and is empty (or untouched if existed).
	>:$ echo "whatthefuck" >> fileA.txt fileB.txt fileC.txt fileD.txt
	whatthefuck fileB.txt fileC.txt fileD.txt
		* Append stdout to fileA
		* Then fileB is treated as a positional argument 
			(echo "start" "fileB" >> fileA)

IV.	Use with 2>>: Stderr and stdout can be appended to the same or different files: command 1>>file1 2>>file2.
	-> the numbers right before >> representes file descriptors:
		* 1 is the file descriptor for standard output (stdout).
		* 2 is the file descriptor for standard error (stderr).
	>:$ cmd 1>>stdout.log 2>>stderr.log
		* This syntax explicitly redirects:
			-File descriptor 1 (stdout) to append to stdout.log.
			-File descriptor 2 (stderr) to append to stderr.log.

By specifying these fds, the shell cleanly separates normal output (stdout) and error messages (stderr) into different files, allowing precise control over where each stream goes.

If no number is provided before > or >>, 1 (stdout) is assumed by default. For example:
V.	Symlink caveat: If the file is a symlink, appending goes to the target file.

*/

static int is_append(t_subproc *process)
{
	(void)process;
	return (0);
}

void	ft_appendre(t_subproc *process)
{
	(void)process;
	is_append(process);
}

