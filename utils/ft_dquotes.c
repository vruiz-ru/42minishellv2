/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dquotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:35:53 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/04 14:50:22 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* ""
-> allow variable and command substitution
-> exmaples:
        >:$ VAR="World"
        >:$ echo "Hello $VAR"      # Prints: Hello World
        >:$ echo "Today is `date`" # Prints: Today is followed by current date
		>:$ VAR="hello"
		>:$ echo "${VAR}world"    # prints: helloworld
		>:$ echo "$VARworld"      # tries to expand $VARworld (likely unset), prints empty or nothing
*/

int	ft_dquotes(t_subproc *process, char *token)
{
	(void)process;
	(void)token;
	return (0);
}