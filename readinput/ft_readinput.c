/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readinput.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:35:16 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/04 22:30:11 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int scan_input(t_subproc *process, char *line)
{
	char    *wildcards;
	char    *buffer;
	int     i;

    (void)process;
	wildcards = "\'\"$";
	i = 0;
	while (line[i])
	{
		buffer = ft_strchr(wildcards, line[i]);
		if (buffer != NULL)
			return (1);
		i++;
	}
    return (0);
}

int	ft_readinput(t_subproc *process)
{
	t_builts  *ptr_built;
	char    *prompt;
	char    *token;

	ptr_built = process->builtins;
	if (process->prompt == NULL)
		prompt = PROMPT_HOME;	
	else
		prompt = process->prompt;
	process->line = readline(prompt);
	if (process->line == NULL)
	{
		free_subprocess(process);
		exit(EXIT_FAILURE);
		return (0);
	}
	if (process->line[0] != '\0')
		add_history(process->line);
	token = ft_strtok(process->line, " ");
	while (token)
	{
		ft_lstadd_back(&ptr_built->tokens, ft_lstnew(token));
		token = ft_strtok(NULL, " ");
	}
	return (free(process->line), process->line = NULL, 1);
}
