/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:20:33 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/01 18:24:57 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_map(char **map)
{
	int	i;

	if (!map || !*map)
		return ;
	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
}

void	free_main(t_utils *shell)
{
	if (shell)
	{
		if (shell->builtins->tokens)
			ft_lstclear(&shell->builtins->tokens, free);
		if (shell->builtins)
			free(shell->builtins);
		if (shell->line)
			free(shell->line);
		if (shell->prompt)
			free(shell->prompt);
		if (shell->name)
			free(shell->name);
		if (shell)
			free(shell);
	}
}
