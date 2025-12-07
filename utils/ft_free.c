/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:20:33 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/05 22:15:41 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// Función auxiliar para borrar un nodo de redirección
void	del_redir(void *content)
{
	t_io	*io;

	io = (t_io *)content;
	if (io->path)
		free(io->path);
    // Si es un heredoc abierto, deberíamos cerrarlo aquí para evitar leaks
    if (io->type == IO_HEREDOC && io->fd != -1)
	{
        close(io->fd);
	}
	free(io);
}

void	free_env_items(char ***map)
{
	char	**ptr;
	int		i;

	ptr = *map;
	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	ptr = NULL;
	*map = ptr;
}
void	ft_free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;
	int		i;

	while (cmds)
	{
		tmp = cmds->next;
		// 1. Liberar argumentos (array de strings)
		if (cmds->args)
		{
			i = 0;
			while (cmds->args[i])
				free(cmds->args[i++]);
			free(cmds->args);
		}
		// 2. Liberar ruta si la buscaste y guardaste (opcional según tu implementación)
		if (cmds->path)
			free(cmds->path);
		// CERRAR FDS Y EVITAR LEAKS
		//if (cmds->fd_in > 2)
		//	close(cmds->fd_in);
		//if (cmds->fd_out > 2)
		//	close(cmds->fd_out);	
		// [AÑADIR] Liberar la lista de redirecciones
        if (cmds->redirs)
            ft_lstclear(&cmds->redirs, del_redir);

		// 3. Liberar la estructura en sí
		free(cmds);
		cmds = tmp;
	}
}

void	free_process(t_process *proc)
{
	if (proc->envs && proc->envs->parent_env)
		free_env_items(&proc->envs->parent_env);
	if (proc->envs && proc->envs->static_env)
		free_env_items(&proc->envs->static_env);
	if (proc->envs)
		free(proc->envs);
	if (proc->prompt && proc->prompt->shell_name)
		free(proc->prompt->shell_name);
	if (proc->prompt && proc->prompt->display)
		free(proc->prompt->display);
	if (proc->prompt && proc->prompt->home_path)
		free(proc->prompt->home_path);
	if (proc->prompt && proc->prompt->current_wd)
		free(proc->prompt->current_wd);
	if (proc->prompt && proc->prompt->last_wd)
		free(proc->prompt->last_wd);
	if (proc->prompt)
		free(proc->prompt);
	if (proc->line)
		free(proc->line);
	if (proc->tokens)
		ft_lstclear(&proc->tokens, free);
	if (proc)
		free(proc);
	proc = NULL;
}

