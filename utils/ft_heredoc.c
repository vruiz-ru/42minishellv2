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
/* "<<" 

Feeds a block of text as stdin to a command.

Edge Cases:

    Delimiters: The ending delimiter (EOF or any chosen word) must appear alone on a line with no leading/trailing spaces.

    Quoting delimiter: If you quote the delimiter (e.g., <<'EOF'), variable and command expansion inside the here-doc is suppressed. Unquoted, expansions occur.

    Leading tabs: <<-EOF (dash/hyphen) strips leading TABs from the here-doc body, allowing you to indent here-doc blocks.

    Multiple here-docs: You can have several here-docs in the same command line (cat <<A <<B ...).

    Accidental file overwrite: Here-doc does NOT itself overwrite files, but if combined with redirection, order matters (e.g., cat <<EOF >file is safe; file is truncated before reading the here-doc).

    Command substitution: If expansions inside the here-doc cause errors (referencing unset vars, for example), it might affect the script’s flow.

    EOF conflicts: If "EOF" (or the delimiter word) appears by chance in the data, the here-doc ends prematurely.

*/

extern int	g_signal_status;

/* Handler especial solo para Heredoc: Cierra STDIN para desbloquear readline */
static void	heredoc_sigint(int sig)
{
	(void)sig;
	g_signal_status = 130;
	write(STDOUT_FILENO, "\n", 1);
	close(STDIN_FILENO); // <--- El truco maestro
}

static void	write_to_tmp(int fd, char *line)
{
	ft_putstr_fd(line, fd);
	ft_putstr_fd("\n", fd);
	free(line);
}
static int	process_heredoc_loop(int fd, char *delimiter)
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
		write_to_tmp(fd, line);
	}
	return (0);
}
/* Función principal limpia y modular */
int	ft_heredoc(char *delimiter)
{
	int		fd;
	int		stdin_backup;
	int		status;

	stdin_backup = dup(STDIN_FILENO);
	if (stdin_backup < 0)
		return (-1);
	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (close(stdin_backup), perror("heredoc open"), -1);
	signal(SIGINT, heredoc_sigint);
	status = process_heredoc_loop(fd, delimiter);
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
