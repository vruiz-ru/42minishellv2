/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:55:02 by aghergut          #+#    #+#             */
/*   Updated: 2025/07/31 21:21:00 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(t_utils *main_struct, char *envp[])
{
	char	**env;
	int     i;

	if (!envp || !*envp)
		return (0);
	(void)main_struct;
	env = envp;
	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
	return (1);
}