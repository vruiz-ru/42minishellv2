/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:41:27 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/02 19:03:39 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <fcntl.h>

static void	heredoc_sigint(int sig)
{
	(void)sig;
	g_signal_status = 130;
	write(STDOUT_FILENO, "\n", 1);
	close(STDIN_FILENO);
}

static void	write_to_tmp(int fd, char *line)
{
	ft_putstr_fd(line, fd);
	ft_putstr_fd("\n", fd);
	free(line);
}

static int	process_heredoc_loop(int fd, char *delimiter, int expand,
		t_process *proc)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			if (g_signal_status == 130)
				return (1);
			break ;
		}
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
		{
			free(line);
			break ;
		}
		if (expand)
		{
			line = ft_expand_heredoc_line(proc, line);
		}
		write_to_tmp(fd, line);
	}
	return (0);
}

int	ft_heredoc(char *delimiter, int expand, t_process *proc)
{
	int	fd;
	int	stdin_backup;
	int	status;

	stdin_backup = dup(STDIN_FILENO);
	if (stdin_backup < 0)
		return (-1);
	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (close(stdin_backup), perror("heredoc open"), -1);
	signal(SIGINT, heredoc_sigint);
	status = process_heredoc_loop(fd, delimiter, expand, proc);
	dup2(stdin_backup, STDIN_FILENO);
	close(stdin_backup);
	close(fd);
	if (status == 1)
	{
		unlink(".heredoc_tmp");
		return (-1);
	}
	fd = open(".heredoc_tmp", O_RDONLY);
	unlink(".heredoc_tmp");
	return (fd);
}
