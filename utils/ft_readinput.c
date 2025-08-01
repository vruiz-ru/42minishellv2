/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readinput.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:35:16 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/01 17:58:00 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_readinput(t_utils *shell)
{
	t_builts  *ptr_built;
	char    *prompt;
	char    *token;

	ptr_built = shell->builtins;
	if (shell->prompt == NULL)
		prompt = PROMPT_HOME;	
	else
		prompt = shell->prompt;
	shell->line = readline(prompt);
	if (shell->line == NULL)
	{
		free_main(shell);
		exit(EXIT_FAILURE);
		return (0);
	}
	if (shell->line[0] != '\0')
		add_history(shell->line);
	token = ft_strtok(shell->line, " ");
	while (token)
	{
		ft_lstadd_back(&ptr_built->tokens, ft_lstnew(token));
		token = ft_strtok(NULL, " ");
	}
	return (free(shell->line), shell->line = NULL, 1);
}
