/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_feats.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 08:07:22 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/05 22:07:02 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

int	dash_feature(t_process *process)
{
	t_list	*token_feat;
	char	*path;

	token_feat = process->tokens->next;
	if (!token_feat->next)
	{
		if (chdir(process->prompt->home_path) != 0)
			return (perror("cd error"), exit(EXIT_FAILURE), 0);
		ft_setpaths(process);
		if (!process->prompt->last_wd || !process->prompt->current_wd)
			return (ft_putstr_fd("Malloc failed\n", 1), 0);
		return (1);
	}
	path = (char *)token_feat->next->content;
	if (chdir(path) != 0)
		ft_printf("cd: %s: No such file or directory\n", path);
	ft_setpaths(process);
	if (!process->prompt->last_wd || !process->prompt->current_wd)
		return (ft_putstr_fd("Malloc failed\n", 1), 0);
	return (1);
}

int	up_feature(t_process *process)
{
	char	*token;
	char	*path;
	int		size;
	
	size = ft_strlen(process->prompt->current_wd);
	if (!ft_strncmp(process->prompt->current_wd, process->prompt->home_path, size))
		return (1);
	path = (char *)process->tokens->next->content;
	token = ft_strtok(path, "/");
	while (token)
	{
		if (!ft_strncmp(token, "--", ft_strlen(token)))
			return(free(token), dash_feature(process));
		if (chdir(token) != 0)
		{
			ft_printf("cd: %s: No such file or directory\n", path);
			return (free(token), 1);
		}
		free(token);
		token = ft_strtok(NULL, "/");
	}
	ft_setpaths(process);
	if (!process->prompt->last_wd || !process->prompt->current_wd)
		return (ft_putstr_fd("Malloc failed\n", 1), 0);
	return (1);
}

int	home_feature(t_process *process)
{
	char	*token_path;
	char	*home_path;
	char	*path;
	int		only_char;

	token_path = (char *)process->tokens->next->content;
	home_path = process->prompt->home_path;
	only_char = 0;
	if (token_path[0] == '~' && !token_path[1])
		only_char = 1;
	if (only_char)
		path = ft_strdup(home_path);
	else
		path = ft_strjoin(home_path, token_path + 1);
	if (!path)
		return (perror("malloc"), exit(EXIT_FAILURE), 0);
	if (chdir(path) != 0)
	{
		ft_printf("cd: %s: No such file or directory\n", token_path);
		return (free(path), 1);
	}	
	ft_setpaths(process);
	if (!process->prompt->last_wd || !process->prompt->current_wd)
		return (free(path), ft_putstr_fd("Malloc failed\n", 1), 0);
	return(free(path), 1);
}

int	back_feature(t_process *process)
{
	char	*last_wd;

	last_wd = process->prompt->last_wd;
	if (chdir(last_wd) != 0)
	{
		ft_printf("cd: %s: No such file or directory\n", last_wd);
		return (1);
	}
	ft_setpaths(process);
	if (!process->prompt->last_wd || !process->prompt->current_wd)
		return (ft_putstr_fd("Malloc failed\n", 1), 0);
	return (ft_pwd(process));
}

int	root_feature(t_process *process)
{
	char	*home_path;
	char	*path;

	if (ft_lstsize(process->tokens) > 2)
	{
		ft_printf("here?\n");
		return (ft_putstr_fd("cd: Too many arguments\n", 1), 1);
	}
		
	home_path = process->prompt->home_path;
	path = (char *)process->tokens->next->content;
	if (chdir(path) == 0)
	{
		ft_putstr_fd("cd: root: Permission denied\n", 1);
		ft_putstr_fd("cd: Moving to home folder\n", 1);
		if (chdir(home_path) != 0)
			return (perror("cd error"), exit(EXIT_FAILURE), 0);
		ft_setpaths(process);
		if (!process->prompt->last_wd || !process->prompt->current_wd)
			return (ft_putstr_fd("Malloc failed\n", 1), 0);
	}
	else
		ft_printf("cd: %s: No such file or directory\n", path);
	return (1);
}
