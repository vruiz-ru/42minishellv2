/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:19:55 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/09 12:50:30 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	assign_value(char **env, char **dest, char *var_name)
{
	char	*value;
	int		idx;
	int		size;
	
	idx = 0;
	while (env[idx])
	{
		size = ft_strchr(env[idx], '=') - env[idx];
		if (!ft_strncmp(env[idx], var_name, size) && env[idx][size] == '=')
		{
			value = ft_strdup(ft_strchr(env[idx], '=') + 1);
			*dest = ft_strjoin_free(*dest, value);
			break ;
		}
		idx++;
	}
}

static int	is_within(char **env, char *var_name)
{
	int	idx;
	int size;
	
	idx = 0;
	while (env[idx])
	{
		size = ft_strchr(env[idx], '=') - env[idx];
		if (!ft_strncmp(env[idx], var_name, size))
			return (1);
		idx++;
	}
	return (0);
}

char	*clean_line(char *content, char token)
{
	char    *seq;
	char	*new;
	int		i;

	i = 0;
	new = NULL;
	seq = "`\"\\";
	if (token == 'n')
		seq = " \t\n`\"'\\*?[]#&;|<>()~";    
	if (!content || !*content)
		return (NULL);
	while (content[i] != '\0')
	{
		if (content[i] == '\\' && ft_strchr(seq, content[i + 1]))
			i++;
		new = ft_addchar(new, content[i]);
		i++;
	}
	return (free(content), new);
}

void scan_char(char *content, char **var_name, int *idx)
{
	char    *stop;

	stop = " \t\n/.,:-+=?!@#^&*()[]{}'\"\\|<>;~";
	if (content[*idx] == '\\' && content[*idx + 1] == '$')
	{
		(*idx)++;
		return ;
	}
	else if (content[*idx] == '$')
	{
		(*idx)++;
		while (content[*idx] != '\0' && !ft_strchr(stop, content[*idx]))
		{
			*var_name = ft_addchar(*var_name, content[*idx]);
			(*idx)++;
		}	
	}
	return ;
}

void	insert_value(t_subproc *process, char **dest, char *var_name)
{
	char	**local_env;
	char	**buffer_env;

	local_env = process->local_env;
	buffer_env = process->buffer_env;
	if (is_within(local_env, var_name))
		assign_value(local_env, dest, var_name);
	else if (is_within(buffer_env, var_name))
		assign_value(buffer_env, dest, var_name);
}
