/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:28:42 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/04 13:20:46 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_checkpair(char *str, char ch)
{
	int	pair;
	int	i;

	pair = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ch)
			pair++;
		i++;
	}
	// ft_printf("pair result -->> %d\non string -->> %s\n", pair, str);
	if (pair % 2 == 0)
		return (1);
	return (0);
}

int	ft_getquote_idx(char *token, char type)
{
	int		idx_normal;
	int		idx_dquote;
	int		idx_squote;
	
	idx_normal = -1;
    idx_squote = -1;
    idx_dquote = -1;
    if (type == '"' && ft_strchr(token, '"'))
        idx_dquote = ft_strchr(token, '"') - token;
	else if (type == '\'' && ft_strchr(token, '\''))
		idx_squote = ft_strchr(token, '\'') - token; 
	else if (ft_strchr(token, ' '))
		idx_normal = ft_strchr(token, ' ') - token;
	if (type == '"' && (idx_normal < 0 || idx_dquote > idx_normal))
		return (idx_dquote);
	if (type == '\'' && (idx_normal < 0 || idx_squote > idx_normal))
		return (idx_squote);
	return (-1);
}
