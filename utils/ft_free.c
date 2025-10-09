/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:20:33 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/09 13:01:26 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_main(t_main *shell)
{
	if (shell->sh_envp)
		ft_mapfree(shell->sh_envp);
	if (shell->line)
		free(shell->line);
	if (shell->prompt)
		free(shell->prompt);
	if (shell->name)
		free(shell->name);
	if (shell->home_path)
		free(shell->home_path);
	if (shell)
		free(shell);
	shell = NULL;
}

void	free_builts(t_builts *ptr)
{
	if (!ptr)
		return ;
	if (ptr->tokens)
		ft_lstclear(&ptr->tokens, free);
	ptr->tokens = NULL;
	if (ptr)
		free(ptr);
	ptr = NULL;
}

void	free_subprocess(t_subproc *ptr)
{
	if (ptr->local_env)
		ft_mapfree(ptr->local_env);
	if (ptr->buffer_env)
		ft_mapfree(ptr->buffer_env);
	if (ptr->builtins && ptr->builtins->tokens)
		ft_lstclear(&ptr->builtins->tokens, free);
	if (ptr->builtins)
		free_builts(ptr->builtins);
	if (ptr->line)
		free(ptr->line);
	if (ptr->prompt)
		free(ptr->prompt);
	if (ptr->current_wd)
		free(ptr->current_wd);
	if (ptr->last_wd)
		free(ptr->last_wd);
	if (ptr->ptr_main)
		free_main(ptr->ptr_main);
	if (ptr)
		free(ptr);
	ptr = NULL;
}
