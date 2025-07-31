/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readinput.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:35:16 by aghergut          #+#    #+#             */
/*   Updated: 2025/07/31 21:11:37 by aghergut         ###   ########.fr       */
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

int	ft_readinput(t_utils **main)
{
	(*main)->prompt = ft_prompt();
	(*main)->line = readline((*main)->prompt);
	if ((*main)->line == NULL)
	{
		free_main(*main);
		exit(EXIT_FAILURE);
		return (0);
	}
	add_history((*main)->line);
	add_tokens((*main)->line, &(*main)->tokens, ' ');
	return (1);
}
