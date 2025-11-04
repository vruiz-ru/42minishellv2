/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 21:02:10 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/04 01:02:07 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static char *get_display_path(t_process *process)
{
	char	*current;
	char	*home;
	char	*buffer;
	char	*temp;
	char	*final;
	size_t	size_current;
	size_t  size_home;

	current = process->prompt->current_wd;
	home = process->prompt->home_path;
	size_current = ft_strlen(current);
	size_home = ft_strlen(home);
	if (size_current == size_home && !ft_strncmp(current, home, size_current))
		return (ft_strdup(HOME));
	temp = ft_strnstr(current, home, size_current);
	if (temp != NULL && temp == current)
	{
		buffer = temp + size_home;
		if (!buffer || !*buffer)
			return (ft_strdup(HOME));
		final = ft_strjoin(HOME, buffer);
		return (final);
	}
	return (ft_strdup(current));
}

char	*ft_prompt(t_process *process)
{
	char	*path;
	char	*prompt;
	char	*final;
	
	path = get_display_path(process);
	if (!path)
		return (perror("malloc"), exit(EXIT_FAILURE), NULL);
	prompt = ft_strjoin(">/", path);
	free(path);
	if (!prompt)
		return (perror("malloc"), exit(EXIT_FAILURE), NULL);
	final = ft_strjoin(prompt, PROMPT_ARROW);
	free(prompt);
	if (!final)
		return (perror("malloc"), exit(EXIT_FAILURE), NULL);
	return (final);
}
