/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:55:02 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/02 18:54:42 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/* mini/builtins/ft_unset.c */
#include "builtins.h"

static int	remove_var(char ***env, char *var_name)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(var_name);
	while ((*env)[i])
	{
		// Buscamos la variable. Debe coincidir el nombre y tener un '=' justo después
		if (!ft_strncmp((*env)[i], var_name, len) && (*env)[i][len] == '=')
		{
			if (ft_mapitem_del(env, i))
				return (1);
			break ;
		}
		i++;
	}
	return (0);
}

int	ft_unset(t_process *process, t_cmd *cmd)
{
	int	i;

	// Ya no necesitamos el doble puntero (**process)
	if (!process || !process->envs->parent_env)
		return (0);

	// Empezamos en 1 porque args[0] es "unset"
	i = 1;
	while (cmd->args[i])
	{
		// Pasamos la dirección de parent_env (&) para poder modificar el array
		remove_var(&process->envs->parent_env, cmd->args[i]);
		i++;
	}
	return (1);
}