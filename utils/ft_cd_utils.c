/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 09:55:23 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/04 13:36:09 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_setpaths(t_subproc *process)
{
	char	**last_wd;
	char	**current_wd;

	last_wd = &process->last_wd;
	current_wd = &process->current_wd;
	if (*last_wd)
		free(*last_wd);
	*last_wd = ft_strdup(*current_wd);
	if (!*last_wd)
		return ;
	free(*current_wd);
	*current_wd = ft_getcwd();
}

int	invalid_options(char *token)
{
	int		idx;
	int		count;
	
	count = 0;
	idx = 0;
	while (token[idx])
	{
		if (count > 2 && idx == count)
			return (1);
		if (token[idx] == '-')
			count++;
		idx++;
	}
	return (0);
} 

int path_input(t_subproc *process)
{
	t_list	*ptr;
	char	*path;

    ptr = process->builtins->tokens->next;
	path = (char *)ptr->content;
	if (ft_isalnum(path[0]))
	{
		if (ptr->next)
			return (ft_putstr_fd("cd: too many arguments\n", 1) ,1);
        if (chdir(path) != 0)
		{
			ft_printf("cd: %s: No such file or directory\n", path);
			return (1);
		}
		ft_setpaths(process);
		if (!process->last_wd || !process->current_wd)
			return (ft_putstr_fd("Malloc failed\n", 1), 0);
        return (1);
	}
	return (0);
}
