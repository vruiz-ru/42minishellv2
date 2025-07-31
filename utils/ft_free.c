/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:20:33 by aghergut          #+#    #+#             */
/*   Updated: 2025/07/31 20:10:26 by aghergut         ###   ########.fr       */
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

void	free_main(t_utils *main_struct)
{
	if (main_struct)
	{
		if (main_struct->tokens)
			free_map(main_struct->tokens);
		if (main_struct->line)
			free(main_struct->line);
		if (main_struct->prompt)
			free(main_struct->prompt);
		if (main_struct->buffer_var)
			free(main_struct->buffer_var);
		if (main_struct->home_path)
			free(main_struct->home_path);
		free(main_struct);
	}
}
