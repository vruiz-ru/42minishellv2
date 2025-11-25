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

int	dash_feature(t_process *process, t_cmd *cmd)
{
	char	*path;

	if (!cmd->args[1] || !ft_strncmp(cmd->args[1], "--", 3))
	{
		if (chdir(process->prompt->home_path) != 0)
			return (perror("cd error"), 1);
		ft_setpaths(process);
		return (0);
	}
	path = cmd->args[1];
	(void)path;
	return (0);
}

int	up_feature(t_process *process, t_cmd *cmd)
{
	char	*test_cwd;
	char	*new_path;

	(void)cmd;
	// 1. Nos movemos físicamente
	if (chdir("..") != 0)
	{
		ft_putstr_fd("minishell: cd: ..: No such file or directory\n", 2);
		return (1);
	}

	// 2. Comprobamos si el terreno es firme (getcwd funciona)
	test_cwd = ft_getcwd();
	
	if (test_cwd)
	{
		// CASO NORMAL: El directorio existe.
		free(test_cwd);
		update_logical_parent(process); // Cortamos la ruta limpiamente (/p1/p2 -> /p1)
	}
	else
	{
		// CASO DIRECTORIO BORRADO (Modo Bash)
		// Imprimimos el error característico
		ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
		
		// En lugar de cortar, añadimos "/.." al final para simular movimiento relativo ciego
		new_path = ft_strjoin(process->prompt->current_wd, "/..");
		if (new_path)
		{
			free(process->prompt->current_wd);
			process->prompt->current_wd = new_path;
		}
	}

	// 3. Sincronizamos (ft_setpaths respetará nuestro current_wd si getcwd falla)
	ft_setpaths(process);
	return (0);
}

int	home_feature(t_process *process, t_cmd *cmd)
{
	char	*path;
	char	*arg;

	arg = cmd->args[1];
	if (!arg || (arg[0] == '~' && !arg[1]))
		path = ft_strdup(process->prompt->home_path);
	else
		path = ft_strjoin(process->prompt->home_path, arg + 1);
	if (!path)
		return (perror("malloc"), 1);
	if (chdir(path) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(path);
		return (1);
	}
	ft_setpaths(process);
	free(path);
	return (0);
}

int	back_feature(t_process *process, t_cmd *cmd)
{
	char	*last_wd;

	(void)cmd;
	last_wd = process->prompt->last_wd;
	if (!last_wd || !*last_wd)
		return (ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2), 1);
	if (chdir(last_wd) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(last_wd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	ft_setpaths(process);
	return (ft_pwd(process, cmd));
}

int	root_feature(t_process *process, t_cmd *cmd)
{
	if (cmd->args[2])
		return (ft_putstr_fd("cd: too many arguments\n", 2), 1);
	if (chdir("/") != 0)
		return (perror("cd"), 1);
	ft_setpaths(process);
	return (0);
}