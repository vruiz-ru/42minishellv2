/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:53:45 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/02 21:14:13 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
char	*ft_searchin(char **env, char *varname)
{
	int	idx_env;
	int	idx_var;

	idx_env = -1;
	while (env[++idx_env])
	{
		idx_var = -1;
		while (env[idx_env][++idx_var] && varname[idx_var] && \
			env[idx_env][idx_var] == varname[idx_var]);
		if (env[idx_env][idx_var] == '=')
			return (env[idx_env] + (idx_var + 1));
	}
	return (NULL);
}

int ft_checkvar(t_subproc *process, char *token)
{
	int	idx;

	idx = 0;
	while (token[idx])
	{
		if ((idx == 0 && token[idx] == '$') || \
		(idx > 0 && token[idx] == '$' && token[idx - 1] != '\\'))
		{
			if (ft_searchin(process->local_env, token + idx))
				return (1);
			if (ft_searchin(process->buffer_env, token + idx))
                return (1);
		}
		idx++;
	}
	return (0);
}

int	ft_parse_tokens(t_subproc *process)
{
	t_list	*tokens;
    t_list  *new;
	char	*token;
	char	*value;
	int		idx;

	tokens = process->builtins->tokens;
	while (tokens)
	{
		token = tokens->content;
		idx = 0;
		while (token[idx])
		{
			if (token[idx] == '$' && token[idx - 1] != '\\' && \
				ft_checkvar(process, token + idx))
				token = ft_newtok(token);
            idx++;
		}
		tokens = tokens->next;
	}
	return (1);
}
*/
