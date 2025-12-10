/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:51:17 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/02 21:43:48 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../input.h"

static int	append_var(t_process *p, char **res, char *str, int i)
{
	char	*var_name;
	char	*val;
	int		start;

	i++;
	if (str[i] == '?')
	{
		val = ft_itoa(p->status);
		*res = ft_strjoin_free(*res, val);
		return (i + 1);
	}
	start = i;
	if (!ft_isalnum(str[i]) && str[i] != '_')
		return (*res = ft_addchar(*res, '$'), i);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	var_name = ft_substr(str, start, i - start);
	val = ft_getvar(p->envs->parent_env, var_name);
	if (!val)
		val = ft_getvar(p->envs->static_env, var_name);
	if (val)
		*res = ft_strjoin_free(*res, val);
	return (free(var_name), i);
}

char	*ft_parse_token(t_process *process, char *str, char token)
{
	char	*res;
	int		i;
	char	quote;

	(void)token;
	if (!str)
		return (NULL);
	res = ft_strdup("");
	i = 0;
	quote = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '"'))
			quote = str[i++];
		else if (quote && str[i] == quote)
		{
			quote = 0;
			i++;
		}
		else if (str[i] == '$' && quote != '\'')
			i = append_var(process, &res, str, i);
		else
			res = ft_addchar(res, str[i++]);
	}
	return (free(str), res);
}

char	*ft_parse_delimiter(char *str, int *quoted)
{
	char	*res;
	int		i;
	char	q;

	if (!str)
		return (NULL);
	res = ft_strdup("");
	i = -1;
	q = 0;
	*quoted = 0;
	while (str[++i])
	{
		if (!q && (str[i] == '\'' || str[i] == '\"'))
		{
			q = str[i];
			*quoted = 1;
		}
		else if (q && str[i] == q)
			q = 0;
		else
			res = ft_addchar(res, str[i]);
	}
	return (free(str), res);
}

char	*ft_expand_heredoc_line(t_process *proc, char *str)
{
	char	*res;
	int		i;

	if (!str)
		return (NULL);
	res = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			i = append_var(proc, &res, str, i);
		else
			res = ft_addchar(res, str[i++]);
	}
	return (free(str), res);
}
