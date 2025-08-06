/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 20:06:37 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/06 10:41:52 by aghergut         ###   ########.fr       */
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

*/

int ft_cd(t_subproc *process)
{
	t_list	*ptr;
	char	*feature;
	int		size;

	ptr = process->builtins->tokens->next;
	feature = (char *)ptr->content;
	size = ft_strlen(feature);
	if (invalid_options(feature))
		return (ft_putstr_fd("cd: invalid options\n", 1), 1);
	if (path_input(process))
		return (1);
	if (!ft_strncmp("..", feature, size) || ft_strnstr(feature, "../", 3))
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
