/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:51:08 by aghergut          #+#    #+#             */
/*   Updated: 2025/07/31 21:10:28 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_getenv(char *envp[])
{
	if (!envp || !*envp)
		return (0);
	while (*envp)
	{
		ft_printf("%s\n", *envp);
		envp++;
	}
	return (1);
}
