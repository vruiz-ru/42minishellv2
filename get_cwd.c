/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:41:00 by aghergut          #+#    #+#             */
/*   Updated: 2025/07/24 13:07:03 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*get_cwd(char *flags)
{
	char	cwd[4096];

	if (flags == NULL)
    {
        if (getcwd(cwd, sizeof(cwd)) == NULL)
        {
            perror("getcwd");
            return (0);
        }
        return (ft_strdup(cwd));
    }
    return (NULL);
}
