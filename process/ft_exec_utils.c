/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:49:41 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/09 14:36:41 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static char	*find_exec_in_paths(char **paths, char *cmd)
{
	char	*path_part;
	char	*exec_path;
	int		i;

	i = -1;
	while (paths[++i])
	{
		path_part = ft_strjoin(paths[i], "/");
		if (!path_part)
			return (NULL);
		exec_path = ft_strjoin(path_part, cmd);
		free(path_part);
		if (!exec_path)
			return (NULL);
		if (access(exec_path, F_OK | X_OK) == 0)
			return (exec_path);
		free(exec_path);
	}
	return (NULL);
}

char	*ft_get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*final_path;
	int		i;

	if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	final_path = find_exec_in_paths(paths, cmd);
	ft_free_array(paths);
	return (final_path);
}

void	cmd_not_found(char *cmd)
{
	char	*msg;
	char	*tmp;

	tmp = ft_strjoin("minishell: ", cmd);
	msg = ft_strjoin(tmp, ": command not found\n");
	free(tmp);
	ft_putstr_fd(msg, 2);
	free(msg);
	exit(127);
}
