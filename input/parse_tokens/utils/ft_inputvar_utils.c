/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inputvar_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:23:06 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/09 18:23:13 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../input.h"

int	contains_variable(char *line)
{
	int	i;

	i = 0;
	if (*line == '$')
		return (1);
	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
		i++;
	if (line[i] == '=')
		return (1);
	return (0);
}

int return_value(t_process *process, char *line)
{
	char	**p_env;
	char	**s_env;
	char	*value;
	int		length;

	value = NULL;
	length = ft_strlen(line);
	p_env = process->envs->parent_env;
	s_env = process->envs->static_env;
	if (length == 1 && ft_specialvars(process, &value, *line))
    {
        ft_safeadd_tokens(&process->tokens, &value);
        return (1);
    }
	value = ft_getvar(p_env, line);
	if (value == NULL)
		value = ft_getvar(s_env, line);
	if (value == NULL)
		return (0);
	ft_safeadd_tokens(&process->tokens, &value);
	return (1);
}
/* Verifica si el siguiente char justifica iniciar la expansión */
int	is_var_start(char c)
{
	// Aceptamos alfanuméricos, guion bajo, interrogación ($?) y el propio $ ($$)
	if (ft_isalnum(c) || c == '_' || c == '?' || c == '$')
		return (1);
	return (0);
}

int	check_ansi_quote(char *line, int idx, char delim)
{
	int	back;
	int	slashes;

	if (delim == '\'' && idx > 0 && line[idx - 1] == '$')
	{
		back = idx - 2;
		slashes = 0;
		while (back >= 0 && line[back] == '\\')
		{
			slashes++;
			back--;
		}
		if (slashes % 2 == 0)
			return (1);
	}
	return (0);
}