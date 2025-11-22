/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:49:41 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/09 14:36:41 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "structs.h"
#include "macros.h"
#include "import/libft/libft.h"
#include "../input/input.h"
#include "../builtins/builtins.h"

#include <signal.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

// HANDLERS
void		ft_sigint(int sig);
// PROCESSES
//int			ft_fork_process(t_process *process, int(*built_f)(t_process *));
int			ft_fork_process(t_process *process);
void    config_pipes(t_cmd *cmd, int *pipefd, int prev_fd);
void    apply_redirections(t_cmd *cmd);
void    close_fds(t_cmd *cmd, int prev_fd);
// UTILS
void	    ft_clear_strtok(void);
int			init_parent(t_process **parent, char *name, char *envp[]);
t_process	*init_child(t_process *parent);
char	    *ft_construct(t_list *tokens, char *str);
void	    free_process(t_process *proc);
void		ft_addspace(t_list **tokens);
void		ft_safeadd_tokens(t_list **tokens, char **token);
// En mini/headers/minishell.h
t_cmd   *ft_new_cmd(void);
int     is_redir(char *str);
void    open_file(t_cmd *cmd, char *symbol, char *file);
int			ft_tokens_to_cmds(t_process *process);
char *ft_get_cmd_path(char *cmd, char **envp);
void ft_free_array(char **arr);
void ft_free_cmds(t_cmd *cmds);

#endif