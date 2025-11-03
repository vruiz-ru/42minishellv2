/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inputvar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:54:08 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/03 21:55:02 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../input.h"

static char	*safe_value(char *line)
{
	char	*value;
	int		idx_line;
	bool	dq;
	bool	sq;
	size_t	len;
	
	idx_line = 0;
	dq = false;
	sq = false;
	while (line[idx_line])
	{
		if (line[idx_line] == ' ' && !dq && !sq)
			break;
		else if (line[idx_line] == '"' && !sq)
			dq = !dq;
		else if (line[idx_line] == '\'' && !dq)
			sq = !sq;
		idx_line++;
	}
	len = idx_line;
	value = ft_substr(line, 0, len);
	if(!value)
		return (perror("malloc"), exit(EXIT_FAILURE), NULL);
	return(value);
}

static char	*construct_variable(char *name, char *value)
{
	char	*variable;

	variable = NULL;
	variable = ft_strdup(name);
	if (!variable)
		return (perror("malloc"), exit(EXIT_FAILURE), NULL);
	if (!ft_strchr(value, '='))
		variable = ft_addchar(variable, '=');
	if (!variable)
		return (perror("malloc"), exit(EXIT_FAILURE), NULL);
	variable = ft_strjoin_free(variable, value);
	if (!variable)
		return (perror("malloc"), exit(EXIT_FAILURE), NULL);
	return (variable);
}

static void	trimmer(char **line, char *delim)
{
	char	*res;
	char	*line_from_delim;
	int		line_len;
	int		from_idx;

	res = NULL;
	line_len = ft_strlen(*line);
	line_from_delim = ft_strnstr(*line, delim, line_len);
	from_idx = line_len - ft_strlen(line_from_delim);
	from_idx += ft_strlen(delim);
	if ((*line)[from_idx])
	{
		res = ft_strdup(*line + from_idx);
		if (!res)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
	}
	free(*line);
	*line = res;	
}

static int	add_to_process_env(t_process *process, char *name, char *value)
{
	char	*var;
	int		idx;

	var = construct_variable(name, value);
	if (!var)
		return (free(name), 0);
	idx = ft_mapitem_index(*&process->envs->static_env, var);
	if (idx >= 0 && !ft_mapitem_replace(&process->envs->static_env, var, idx))
		return (free(var), free(name), 0);
	else if (!ft_mapitem_add(&process->envs->static_env, var))
		return (free(var), free(name), 0);
	return (free(var), free(name), 1);
}

int	ft_inputvar(t_process *process, char **line)
{
	char	*name;
	char	*value;

	name = ft_strtok(*line, "=");
	value = safe_value(ft_strchr(*line, '='));
	process->is_variable = true;
	if (!ft_std(process, value) && !ft_quote(process, value))
		return (0);
	trimmer(line, value);
	value = ft_construct(process->tokens, value);
	if (!add_to_process_env(process, name, value))
		return (0);
	ft_lstclear(&process->tokens, free);
	process->tokens = NULL;
	process->is_variable = false;
	ft_clear_strtok();
	return (1);
}
