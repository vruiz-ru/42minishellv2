/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 20:06:37 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/02 18:56:52 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
/*

On success, zero is returned.  On error, -1 is returned, and  errno  is
	   set to indicate the error.
".."	~= moving up one folder
"~"		= home directory
"-"		= Switches to the previous working directory.
"."		= Stays in the current directory (no actual movement).
"/" 	= Moves to the root directory.
"--" 	= End of options; the rest is taken as the directory path (useful if a directory name starts with a dash).
"/absolute/path or cd relative/path"= Moves to the specified absolute or relative path.

!!!! new: -L -P valid options:

	-L: Follow symbolic links (default behavior). -L stands for link
	example:
			first we create an example 
					$>: mkdir /home/user/Documents/dir_example
			second make an symbol link for a path
					$>: ln -s /home/user/Documents/projectA_example ~/symlink_to_example
			third we move to the symbol link
					$>: cd -L ~/symlink_to_example
					$>~/symlink_to_example: *we are here*

	-P: Do not follow symbolic links. -P stands for original path
	example:
			first we create an example 
					$>: mkdir /home/user/Documents/dir_example
			second make an symbol link for a path
					$>: ln -s /home/user/Documents/projectA_example ~/symlink_to_example
			third we move to the symbol link
					$>: cd -L ~/symlink_to_example
					$>/home/user/Documents/projectA_example: *we are here*
	
					
!!!! resolve "$> cd" simple to go to home directory

*/

static int  ft_home(t_process *process)
{
    if (chdir(process->prompt->home_path) != 0)
        ft_putstr_fd("cd: Failed returning to home path\n", 2);
    ft_setpaths(process);
    return (1);
}

int ft_cd(t_process *process, t_cmd *cmd)
{
    char    *arg;

    // 1. Si no hay argumentos ("cd"), vamos a casa
    if (!cmd->args[1])
        return (ft_home(process));
    
    arg = cmd->args[1];

    // 2. Revisar opciones inválidas (comienzan por - pero no son - o --)
    if (invalid_options(arg))
        return (ft_putstr_fd("cd: invalid options\n", 2), 1);

    // 3. Features específicas
    if (!ft_strncmp(arg, "..", 2))
        return (up_feature(process, cmd));
        
    if (arg[0] == '~')
        return (home_feature(process, cmd));
        
    if (!ft_strncmp(arg, "-", 2) && !arg[1])
        return (back_feature(process, cmd));
        
    if (!ft_strncmp(arg, "--", 3)) // Solo -- sin nada más
        return (dash_feature(process, cmd));

    // 4. Si no es feature, es un path normal o root
    return (path_input(process, cmd));
}
