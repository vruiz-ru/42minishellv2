/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:07:18 by aghergut          #+#    #+#             */
/*   Updated: 2025/07/31 20:10:16 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int valid_cmd(char line, char *envp[])
{
	char	*cmd_token;
	char	*path_token;
	char	**path;
	int		i;

	i = 0;
	while (envp[i])
	{
		path = ft_split(envp[i], '=');
		if (path == NULL)
			return(perror("invalid split"), 0);
		if (!_ft_strncmp(path[0], "PATH", ft_strlen(path[0])))
		{
			path_token = ft_strtok(path[0], ":");
			while (path_token)
			{
				path_token = ft_strtok(NULL, ":");
            }
		}
	}
}
