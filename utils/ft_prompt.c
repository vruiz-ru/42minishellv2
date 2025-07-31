/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:38:22 by aghergut          #+#    #+#             */
/*   Updated: 2025/07/31 21:42:14 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* I don't know if I need this if we are walking thru the new created directories

char    *current_prompt(char *cwd)
{
	char	*path;
	int 	idx;
	int 	dirs_path;

	path = NULL;
	idx = 0;
	dirs_path = 0;
	if (cwd[0] == '/')
	{
		while (cwd[idx])
		{
			if (cwd[idx] == '/')
				dirs_path = idx + 1;
			idx++;
		}
		path = ft_strdup(cwd + dirs_path);
		free(cwd);	
	}
	return (path);
}
*/ 

char	*ft_prompt(t_utils *main_struct)
{
	char	*cwd;
	char	*base;
	char	*res;
	
	cwd = ft_getcwd(main_struct, NULL);
	base = ft_strrchr(cwd, '/') + 1;
	res = NULL;
	if (!ft_strncmp(base, NAME, ft_strlen(NAME)))
		res = ft_strjoin("/~ ", PROMPT);
	else
		res = ft_strdup(cwd);
	free(cwd);
	return (res);
}

