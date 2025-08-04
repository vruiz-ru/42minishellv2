/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:41:27 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/04 22:30:56 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static int	is_heredoc(t_subproc *process)
{
	(void)process;
	return (0);
}

void	ft_heredoc(t_subproc *process)
{
	(void)process;
	is_heredoc(process);
}