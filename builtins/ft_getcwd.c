/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getcwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:41:00 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/01 18:14:34 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getcwd(void)
{
	char	cwd[4096];
	char    *res;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return (0);
	}
	res = ft_strdup(cwd);
	return (res);
}

int ft_pwd(t_utils *shell)
{
	char    *dir_path;
	char	*buff;

	buff = ft_getcwd();
	dir_path = ft_strnstr(buff, shell->name, ft_strlen(buff));
	if (!dir_path)
		return (0);
	ft_printf("%s\n", dir_path);
	free(buff);
	return (1);
}