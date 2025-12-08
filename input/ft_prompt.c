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

static char	*try_home_replacement(char *current, char *home)
{
	size_t	len;

	len = ft_strlen(home);
	if (ft_strncmp(current, home, len) == 0)
	{
		if (current[len] == '\0')
			return (ft_strdup(HOME));
		if (current[len] == '/')
			return (ft_strjoin(HOME, current + len));
	}
	return (NULL);
}

static char	*get_display_path(t_process *process)
{
	char	*current;
	char	*home;
	char	*result;

	current = process->prompt->current_wd;
	home = process->prompt->home_path;
	if (!current)
		return (ft_strdup("?"));
	if (home && *home)
	{
		result = try_home_replacement(current, home);
		if (result)
			return (result);
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
	prompt = ft_strjoin(">", path);
	free(path);
	if (!prompt)
		return (perror("malloc"), exit(EXIT_FAILURE), NULL);
	final = ft_strjoin(prompt, PROMPT_ARROW);
	free(prompt);
	if (!final)
		return (perror("malloc"), exit(EXIT_FAILURE), NULL);
	return (final);
}
