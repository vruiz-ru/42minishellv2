/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_squotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:34:35 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/04 14:48:19 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* ''
-> Everything inside '...' is preserved exactly as typed.
examples:
        >:$ VAR="World"
        >:$ echo 'Hello $VAR'    # Prints: Hello $VAR
        >:$ echo 'Today is `date`'  # Prints: Today is `date`
        >:$ echo 'It'\''s safe'   # Prints: It's safe

*/

int	ft_squotes(t_subproc *process, char *token)
{
	(void)process;
	(void)token;
	return (0);
}