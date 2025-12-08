/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_construct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:54:14 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/02 19:01:34 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	static_variable(char *str)
{
	if (ft_strchr(str, '='))
		return (1);
	return (0);
}

static char	*copy_content(char *dst, char *src)
{
	int	i;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i])
	{
		dst = ft_addchar(dst, src[i]);
		if (dst == NULL)
			return (NULL);
		i++;
	}
	return (dst);
}

char	*ft_construct(t_list *tokens, char *str)
{
	t_list	*args;
	char	*content;

	args = tokens;
	if (!static_variable(str))
		args = args->next;
	if (str)
		free(str);
	str = NULL;
	while (args)
	{
		content = (char *)args->content;
		str = copy_content(str, content);
		args = args->next;
	}
	return (str);
}
