/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 11:32:12 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/09 14:31:04 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static t_process	*init(void)
{
	t_process	*process;
	
	process = malloc(sizeof(t_process));
	if (!process)
		return (perror("malloc"), exit(EXIT_FAILURE), NULL);
	ft_memset(process, 0, sizeof(t_process));
	process->envs = malloc(sizeof(t_envs));
	process->prompt = malloc(sizeof(t_prompt));
	if (!process->envs && !process->prompt)
		return (perror("malloc"), exit(EXIT_FAILURE), NULL);
	ft_memset(process->envs, 0, sizeof(t_envs));
	ft_memset(process->prompt, 0, sizeof(t_prompt));
	return (process);
}

t_process	*init_child(t_process *parent)
{
	t_process	*child;
	
	child = init();
	if (!child)
		return (NULL);
	child->envs->parent_env = ft_mapdup(parent->envs->parent_env);
	if (!child->envs->parent_env)
		return (perror("malloc"), exit(EXIT_FAILURE), NULL);
	child->prompt->current_wd = ft_strdup(parent->prompt->current_wd);
	if (!child->prompt->current_wd)
		return (perror("malloc"), exit(EXIT_FAILURE), NULL);
	child->prompt->last_wd = ft_strdup(child->prompt->current_wd);
	if (!child->prompt->last_wd)
		return (perror("malloc"), exit(EXIT_FAILURE), NULL);
	child->pid = getpid();
    child->forks -= 1;
    child->status = 0;
	return (child);
}
/* Nueva función para incrementar SHLVL */
static void	increment_shell_level(t_process *proc)
{
	char	*lvl_str;
	char	*entry;
	int		lvl;
	int		idx;

	lvl_str = ft_getvar(proc->envs->parent_env, "SHLVL");
	lvl = 0;
	if (lvl_str)
		lvl = ft_atoi(lvl_str);
	free(lvl_str);
	lvl_str = ft_itoa(lvl + 1);
	if (!lvl_str)
		return ;
	entry = ft_strjoin("SHLVL=", lvl_str);
	free(lvl_str);
	if (!entry)
		return ;
	idx = ft_mapitem_index(proc->envs->parent_env, "SHLVL");
	if (idx >= 0)
		ft_mapitem_replace(&proc->envs->parent_env, entry, idx);
	else
		ft_mapitem_add(&proc->envs->parent_env, entry);
	free(entry);
}

int	init_parent(t_process **parent, char *name, char *envp[])
{
	*parent = init();
	if (!*parent)
		return (0);
	
	// 1. Duplicamos el entorno primero (necesario para buscar HOME después)
	(*parent)->envs->parent_env = ft_mapdup(envp);
	if (!(*parent)->envs->parent_env)
		return (perror("malloc"), exit(EXIT_FAILURE), 0);
	
	(*parent)->prompt->shell_name = ft_strdup(name);
	if (!(*parent)->prompt->shell_name)
		return (perror("malloc"), exit(EXIT_FAILURE), 0);

	// CORRECCIÓN: Si HOME no existe, se queda NULL. No usamos getcwd().
	(*parent)->prompt->home_path = ft_getvar((*parent)->envs->parent_env, "HOME");

	// 3. El directorio actual e inicial (PWD/OLDPWD) sí es getcwd()
	(*parent)->prompt->current_wd = ft_getcwd();
	if (!(*parent)->prompt->current_wd)
		return (perror("malloc"), exit(EXIT_FAILURE), 0);
	
	(*parent)->prompt->last_wd = ft_getcwd();
	if (!(*parent)->prompt->last_wd)
		return (perror("malloc"), exit(EXIT_FAILURE), 0);
	
	(*parent)->forks = 1;
	(*parent)->pid = getpid();
	(*parent)->status = 0;

	// 4. Incrementamos SHLVL
	increment_shell_level(*parent);

	return (1);
}
