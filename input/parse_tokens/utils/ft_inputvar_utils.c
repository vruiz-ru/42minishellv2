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

int add_variable(char ***map, char *item)
{
	size_t idx;

	if (!item)
		return (0);
	if (already_exists(*map, item))
	{
		idx = ft_mapitem_index(*map, item);
		if (!ft_mapitem_replace(map, item, idx))
			return (0);
	}
	if (!ft_mapitem_add(map, item))
		return (0);
	return (1);
}

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