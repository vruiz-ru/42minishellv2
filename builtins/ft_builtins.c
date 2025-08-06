/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:21:54 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/05 16:44:18 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_varformat(char *token)
{
	int	i;

	i = 0;
	while (token[i] && (ft_isalnum(token[i]) || token[i] == '_'))
		i++;
	if (token[i] == '=')
		return (1);
	return (0);
}

int	ft_builtins(t_subproc *process)
{
	char    *cmd;
	int		size;

	cmd = (char *)process->builtins->tokens->content;
	size = ft_strlen(cmd);
    if (!ft_strncmp(cmd, "clear", size))
		ft_clear();
	else if (!ft_strncmp(cmd, "exit", size) && !ft_exit(process))
		return (0);	
	else if (!ft_strncmp(cmd, "export", size) && !ft_export(process))
		return (0);
	else if (!ft_strncmp(cmd, "pwd", size) && !ft_pwd(process))
		return (0);
	else if (!ft_strncmp(cmd, "env", size) && !ft_getenv(process))
		return (0);	
	else if (!ft_strncmp(cmd, "echo", size) && !ft_echo(process))
		return (0);
	else if (!ft_strncmp(cmd, "unset", size) && !ft_unset(&process))
		return (0);
	else if (is_varformat(cmd) && !ft_mapitem_add(&process->buffer_env, cmd))
        return (0);
    else if (!ft_strncmp(cmd, "cd", size) && !ft_cd(process))
		return (0);	
	return (1);
}
