/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 11:32:12 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/09 13:00:26 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int init_builtins(t_builts **builts)
{
	*builts =(t_builts *) malloc(sizeof(t_builts));
	if (!*builts)
		return (perror("malloc builts"), 0);
	(*builts)->tokens = NULL;
	(*builts)->flags = false;
	(*builts)->double_quotes = false;
	(*builts)->single_quotes = false;
	(*builts)->in_file = false;
	(*builts)->out_file = false;
	return (1);
}

int	init_subproc(t_main *shell, t_subproc **sub)
{
	*sub = (t_subproc *)malloc(sizeof(t_subproc));
	if (!*sub)
		return (perror("malloc subproc"), 0);
    ft_memset(*sub, 0, sizeof(t_subproc));
	if (!init_builtins(&(*sub)->builtins))
		return (free(sub), perror("malloc builts"), 0);
	(*sub)->ptr_main = shell;
	(*sub)->local_env = ft_mapdup(shell->sh_envp);
    (*sub)->current_wd = ft_getcwd();
    (*sub)->last_wd = ft_getcwd();
	return (1);
}

int	init_main(t_main **shell, char *name, char *envp[])
{
	*shell = malloc(sizeof(t_main));	
	if (!*shell)
		return (perror("malloc main"), 0);
    (*shell)->status = 1;
	(*shell)->sh_envp = ft_mapdup(envp);
	(*shell)->prompt = NULL;
	(*shell)->line = NULL;
	(*shell)->running = true;
	(*shell)->name = ft_strdup(name + 1);
    (*shell)->home_path = ft_getcwd();
	return (1);
}
