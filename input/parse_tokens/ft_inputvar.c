/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inputvar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:54:08 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/09 17:59:26 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../input.h"

static char	*safe_value(char *line)
{
	int		i;
	bool	dq;
	bool	sq;

	i = 0;
	dq = false;
	sq = false;
	while (line[i])
	{
		if (line[i] == ' ' && !dq && !sq)
			break ;
		else if (line[i] == '"' && !sq)
			dq = !dq;
		else if (line[i] == '\'' && !dq)
			sq = !sq;
		i++;
	}
	return (ft_substr(line, 0, i));
}

static void	trimmer(char **line, char *name, char *val)
{
	char	*res;
	size_t	cut_len;

	cut_len = ft_strlen(name) + 1 + ft_strlen(val);
	if ((*line)[cut_len])
		res = ft_strdup(*line + cut_len);
	else
		res = ft_strdup("");
	if (!res)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	free(*line);
	*line = res;
}

static int	add_var(t_process *proc, char *n, char *v)
{
	char	*var;
	int		idx;

	var = ft_strjoin(n, "=");
	if (!var)
		return (free(n), 0);
	var = ft_strjoin_free(var, v);
	if (!var)
		return (free(n), 0);
	idx = ft_mapitem_index(proc->envs->static_env, var);
	if (idx >= 0)
	{
		if (!ft_mapitem_replace(&proc->envs->static_env, var, idx))
			return (free(var), free(n), 0);
	}
	else if (!ft_mapitem_add(&proc->envs->static_env, var))
		return (free(var), free(n), 0);
	return (free(var), free(n), 1);
}

static int	get_data(char *line, char **name, char **val)
{
	char	*eq;

	eq = ft_strchr(line, '=');
	if (!eq)
		return (0);
	*val = safe_value(eq + 1);
	if (!*val)
		return (0);
	*name = ft_substr(line, 0, eq - line);
	if (!*name)
	{
		free(*val);
		return (0);
	}
	return (1);
}

int	ft_inputvar(t_process *p, char **line)
{
	char	*name;
	char	*val;

	if (*(*line) == '$')
	{
		if (return_value(p, *line + 1))
			return (1);
		return (1);
	}
	if (!get_data(*line, &name, &val))
		return (0);
	if (*val)
	{
		p->is_variable = true;
		if (!ft_tokenize_line(p, val))
			return (free(name), free(val), 0);
		trimmer(line, name, val);
		val = ft_construct(p->tokens, val);
		ft_lstclear(&p->tokens, free);
		p->tokens = NULL;
		p->is_variable = false;
	}
	else
		trimmer(line, name, val);
	return (add_var(p, name, val));
}
