/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:28:42 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/08 14:35:22 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
static void scan(char *content, char *new, char *var_name, int *idx)
{
	char    *stop;

	stop = " \t\n/.,:-+=?!@#^&*()[]{}'\"\\|<>;~";
	if (content[*idx] == '\\' && content[*idx + 1] == '$')
	{
		(*idx)++;
		return ;
	}
	if (content[*idx] == '$')
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


char	*ft_parse_token(t_subproc *process, char *content)
{
	char	*res;
	char	*var_name;
	int		i;

	i = 0;
	content = ft_cleanline(content);
	res = NULL;
	while (content[i] != '\0')
	{
		var_name = NULL;
		ft_scanning_variable(content, &var_name, &i);
		if (var_name != NULL)
		{
			ft_insert(process, &res, var_name);
			if (!res)
				return (NULL);
		}
		ft_scanning_quotes(content, &res, &i);
		res = ft_addchar(res, content[i]);
		i++;
	}
	return (res);	
}
*/