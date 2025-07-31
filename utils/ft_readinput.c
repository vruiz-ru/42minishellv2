/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readinput.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:35:16 by aghergut          #+#    #+#             */
/*   Updated: 2025/07/31 21:34:17 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_tokens(char *line, char delimiter)
{
	int	count;
	int	inside;

	count = 0;
	inside = 0;
	while (*line)
	{
		if (*line != delimiter && !inside)
		{
			inside = 1;
			count++;
		}
		if (*line == delimiter)
			inside = 0;
		line++;
	}
	return (count);
}

static void	add_tokens(char *line, char	***tokens, char delimiter)
{
	char	*token;
	int		map_size;
	int		map_idx;

	map_size = count_tokens(line, delimiter);
	*tokens = malloc((map_size + 1) * sizeof(char *));
	if (!*tokens)
		return ;
	token = ft_strtok(line, " ");
	
	map_idx = 0;
	while (token)
	{
		(*tokens)[map_idx++] = ft_strdup(token);
		free(token);
		token = ft_strtok(NULL, " ");
	}
	(*tokens)[map_idx] = NULL;
}

int	ft_readinput(t_utils **main_struct)
{
	(*main_struct)->prompt = ft_prompt(*main_struct);
	(*main_struct)->line = readline((*main_struct)->prompt);
	if ((*main_struct)->line == NULL)
	{
		free_main(*main_struct);
		exit(EXIT_FAILURE);
		return (0);
	}
	add_history((*main_struct)->line);
	add_tokens((*main_struct)->line, &(*main_struct)->tokens, ' ');
	return (1);
}
