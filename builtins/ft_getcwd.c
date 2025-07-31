/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getcwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:41:00 by aghergut          #+#    #+#             */
/*   Updated: 2025/07/31 21:53:14 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getcwd(t_utils *main_struct, char *flags)
{
	char	cwd[4096];
    
	if (flags == NULL)
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			perror("getcwd");
			return (0);
		}
        main_struct->home_path = ft_strdup(cwd);
        return (main_struct->home_path);
	}
	return (NULL);
}

int ft_pwd(t_utils *main_struct, char *flags)
{
    char    *res;

    res = ft_getcwd(main_struct, flags);
    if (!res)
        return (0);
    ft_printf("%s\n", res);
    return (1);
}