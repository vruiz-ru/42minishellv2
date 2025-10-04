/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_feats.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 08:07:22 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/04 13:38:15 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	dash_feature(t_subproc *process)
{
	t_list	*token_feat;
	char	*path;

	token_feat = process->builtins->tokens->next;
	if (!token_feat->next)
	{
		if (chdir(process->ptr_main->home_path) != 0)
			return (perror("cd error"), 0);
		ft_setpaths(process);
		if (!process->last_wd || !process->current_wd)
			return (ft_putstr_fd("Malloc failed\n", 1), 0);
		return (1);
	}
	path = (char *)token_feat->next->content;
	if (chdir(path) != 0)
		ft_printf("cd: %s: No such file or directory\n", path);
	ft_setpaths(process);
	if (!process->last_wd || !process->current_wd)
		return (ft_putstr_fd("Malloc failed\n", 1), 0);
	return (1);
}

int	up_feature(t_subproc *process)
{
	char	*token;
	char	*path;

	path = (char *)process->builtins->tokens->next->content;
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
	if (!process->last_wd || !process->current_wd)
		return (ft_putstr_fd("Malloc failed\n", 1), 0);
	return (1);
}

int	home_feature(t_subproc *process)
{
	char	*token_path;
	char	*home_path;
	char	*path;
	int		only_char;

	token_path = (char *)process->builtins->tokens->next->content;
	home_path = process->ptr_main->home_path;
	only_char = 0;
	if (token_path[0] == '~' && !token_path[1])
		only_char = 1;
	if (only_char)
		path = ft_strdup(home_path);
	else
		path = ft_strjoin(home_path, token_path + 1);
	if (chdir(path) != 0)
	{
		ft_printf("cd: %s: No such file or directory\n", token_path);
		return (free(path), 1);
	}	
	ft_setpaths(process);
	if (!process->last_wd || !process->current_wd)
		return (free(path), ft_putstr_fd("Malloc failed\n", 1), 0);
	return(free(path), 1);
}

int	back_feature(t_subproc *process)
{
	char	*last_wd;

	last_wd = process->last_wd;
	if (chdir(last_wd) != 0)
	{
		ft_printf("cd: %s: No such file or directory\n", last_wd);
		return (1);
	}
	ft_setpaths(process);
	if (!process->last_wd || !process->current_wd)
		return (ft_putstr_fd("Malloc failed\n", 1), 0);
	return (ft_pwd(process));
}

int	root_feature(t_subproc *process)
{
	char	*home_path;
	char	*path;

	if (ft_lstsize(process->builtins->tokens) > 2)
		return (ft_putstr_fd("cd: Too many arguments\n", 1), 1);
	home_path = process->ptr_main->home_path;
	path = (char *)process->builtins->tokens->next->content;
	if (chdir(path) == 0)
	{
		ft_putstr_fd("cd: root: Permission denied\n", 1);
		ft_putstr_fd("cd: Moving to home folder\n", 1);
		if (chdir(home_path) != 0)
			return (perror("cd error"), 0);
		ft_setpaths(process);
		if (!process->last_wd || !process->current_wd)
			return (ft_putstr_fd("Malloc failed\n", 1), 0);
	}
	else
		ft_printf("cd: %s: No such file or directory\n", path);
	return (1);
}
