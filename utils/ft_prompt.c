/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 21:02:10 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/04 13:21:25 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_prompt(t_subproc *process)
{
	char	*current_path;
	char	*home_path;
	char	*buffer;
	char	*prompt;
	size_t	size_current;
	size_t  size_home;
	
	current_path = process->current_wd;
	home_path = process->ptr_main->home_path;
	size_current = ft_strlen(current_path);
	size_home = ft_strlen(home_path);
	if (!ft_strncmp(current_path, home_path, size_current))
		return (ft_strjoin(">/~", PROMPT_ARROW));
	buffer = ft_strnstr(current_path, home_path, size_current) + size_home;
	prompt = ft_strjoin(">/~", buffer);
	if (!prompt)
		return (NULL);
	buffer = ft_strjoin(prompt, PROMPT_ARROW);
	return (free(prompt), buffer);
}
