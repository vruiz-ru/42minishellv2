/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 11:17:20 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/09 11:17:39 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*read_from_pipe(int *pipefds)
{
	char	buffer[1024];
	char	*line;
	int		size;

	close(pipefds[1]);
	read(pipefds[0], buffer, 1024);
	if (read)
		buffer[read] == '\0';
	if (!buffer)
		return (NULL);
	line = ft_strdup(buffer);
	if (!line)
		return (perror("malloc"), exit(EXIT_FAILURE), NULL);
	return (line)
}

void	*write_to_pipe(char *content, int *pipefds)
{
	int	size;

	close(pipefds[0]);
	size = 0;
	if (content && *content)
		size = ft_strlen(content);
	write(pipefds[1], content, size);
}
