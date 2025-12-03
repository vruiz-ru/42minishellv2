/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:19:55 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/09 19:32:54 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../input.h"

static int	assign_value(char **env, char **dest, int idx)
{
	char	*value;
	
	value = ft_strdup(ft_strchr(env[idx], '=') + 1);
	if (!value)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
		return (0);
	}
	*dest = ft_strjoin_free(*dest, value);
	if (!*dest)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
		return (0);
	}
	return (1);
}

int	already_exists(char **env, char *var_name)
{
	int	idx;
	int len_invar;
	int	len_cmpvar;
	
	idx = 0;
	len_cmpvar = ft_strlen(var_name);
	while (env && env[idx])
	{
		len_invar = -1;
		if (ft_strchr(env[idx], '='))
			len_invar = ft_strchr(env[idx], '=') - env[idx];
		if (len_invar && len_invar == len_cmpvar && \
			!ft_strncmp(env[idx], var_name, len_invar))
				return (idx);	
		idx++;
	}
	return (-1);
}

char	*clean_line(char *content, char token)
{
	char	*seq;
	char	*new;
	int		i;

	i = 0;
	new = NULL;
	seq = "`\"\\"; // Default para comillas dobles
	
	// CAMBIO CRÍTICO: En modo normal ('n'), no escapamos NADA.
	// El subject dice "no interpretar \", así que vaciamos seq.
	if (token == 'n')
		seq = ""; 
	
	while (content[i] != '\0')
	{
		if (content[i] == '\\' && ft_strchr(seq, content[i + 1]))
		{
			i++;
			new = ft_addchar(new, content[i]);
		}
		else
			new = ft_addchar(new, content[i]);
		i++;
	}
	return (free(content), new);
}

void	scan_char(t_process *process, char *content, char **var_name, int *idx)
{
	char	*stop;

	stop = " \t\n/.,:-+=?!@#^&*()[]{}'\"\\|<>;~";
	if (content[*idx] == '\\' && content[*idx + 1] == '$')
	{
		(*idx)++;
		return ;
	}
	else if (content[*idx] == '$' && is_var_start(content[*idx + 1]))
	{
		(*idx)++;
		if (ft_specialvars(process, var_name, content[*idx]))
		{
			(*idx)++;
			return ;   
		}
		while (content[*idx] && !ft_strchr(stop, content[*idx]))
		{
			*var_name = ft_addchar(*var_name, content[*idx]);
			(*idx)++;
		}
	}
	return ;
}

void	insert_value(t_process *process, char **dest, char *var_name)
{
	char	**process_env;
	char	**static_env;
	int		founded;

	process_env = process->envs->parent_env;
	static_env = process->envs->static_env;
	founded = already_exists(static_env, var_name);
	if (founded >= 0 && assign_value(static_env, dest, founded))
		return ;
	founded = already_exists(process_env, var_name);
	if (founded >= 0 && assign_value(process_env, dest, founded))
		return ;
}