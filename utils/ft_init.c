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

int	init_parent(t_process **parent, char *name, char *envp[])
{
	*parent = init();
	if (!*parent)
		return (0);
	(*parent)->envs->parent_env = ft_mapdup(envp);
	if (!(*parent)->envs->parent_env)
		return (perror("malloc"), exit(EXIT_FAILURE), 0);
	(*parent)->prompt->shell_name = ft_strdup(name);
	if (!(*parent)->prompt->shell_name)
		return (perror("malloc"), exit(EXIT_FAILURE), 0);
	(*parent)->prompt->home_path = ft_getcwd();
	if (!(*parent)->prompt->home_path)
		return (perror("malloc"), exit(EXIT_FAILURE), 0);
	(*parent)->prompt->current_wd = ft_getcwd();
	if (!(*parent)->prompt->current_wd)
		return (perror("malloc"), exit(EXIT_FAILURE), 0);
	(*parent)->prompt->last_wd = ft_getcwd();
	if (!(*parent)->prompt->last_wd)
		return (perror("malloc"), exit(EXIT_FAILURE), 0);
    (*parent)->forks = 1;
	(*parent)->pid  = getpid();
    (*parent)->status = 0;
	return (1);
}
