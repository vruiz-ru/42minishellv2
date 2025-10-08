/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readinput.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:35:16 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/08 14:01:47 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_readinput(t_subproc *process)
{
	process->prompt = ft_prompt(process);
	if (process->prompt == NULL)
		return (perror("malloc"), 0);
	process->line = readline(process->prompt);
	if (process->line == NULL)
	{
		free_subprocess(process);
		exit(EXIT_FAILURE);
		return (0);
	}
	if (process->line[0] != '\0')
		add_history(process->line);
	ft_create_tokens(process);
	// ft_parse_tokens(process);
	return (free(process->line), process->line = NULL, 1);
}
