/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 20:06:37 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/04 13:19:05 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static int  ft_home(t_subproc *process)
{
	char    *home_path;

	home_path = process->ptr_main->home_path;
	if (chdir(home_path) != 0)
		ft_putstr_fd("cd: Failed returning to home path!", 1);
	ft_setpaths(process);
	return (1);
}

int ft_cd(t_subproc *process)
{
	t_list	*ptr;
	char	*feature;
	int		size;

    ptr = process->builtins->tokens->next;
	if (ptr == NULL)
		return(ft_home(process));
	feature = (char *)ptr->content;
	size = ft_strlen(feature);
	if (invalid_options(feature))
		return (ft_putstr_fd("cd: invalid options\n", 1), 1);
	if (path_input(process))
		return (1);
	if ((!ft_strncmp("..", feature, size) || ft_strnstr(feature, "../", 3)) \
		&& !ft_strchr(process->prompt, '~'))
		return (up_feature(process));
	if (ft_strnstr(feature, "~/", 2) || feature[0] == '~')
		return (home_feature(process));
	if (!ft_strncmp("-", feature, size))
		return (back_feature(process));
	if (feature[0] == '/')
		return (root_feature(process));
	if (!ft_strncmp("--", feature, size))
		return (dash_feature(process));
	return (1);
}
