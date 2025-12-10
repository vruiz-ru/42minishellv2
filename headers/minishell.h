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

# include "../builtins/builtins.h"
# include "../input/input.h"
# include "import/libft/libft.h"
# include "macros.h"
# include "structs.h"
# include <errno.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

// VARIABLE GLOBAL
extern int	g_signal_status;
// HANDLERS
void		ft_sigint(int sig);
// PROCESSES
int			ft_fork_process(t_process *process);
void		config_pipes(t_cmd *cmd, int *pipefd, int prev_fd);
void		apply_redirections(t_cmd *cmd);
void		close_fds(t_cmd *cmd, int prev_fd);
void		cmd_not_found(char *cmd);
// UTILS
void		ft_clear_strtok(void);
int			init_parent(t_process **parent, char *name, char *envp[]);
char		*ft_construct(t_list *tokens, char *str);
void		free_process(t_process *proc);
void		ft_addspace(t_list **tokens);
void		ft_safeadd_tokens(t_list **tokens, char **token);
// EXEC
t_cmd		*ft_new_cmd(void);
int			is_redir(char *str);
void		ft_cmdadd_back(t_cmd **lst, t_cmd *new);
void		ft_add_io(t_cmd *cmd, t_io_type type, char *path, int fd);
int			ft_apply_redirs(t_cmd *cmd);
int			ft_tokens_to_cmds(t_process *process);
char		*ft_get_cmd_path(char *cmd, char **envp);
void		ft_free_array(char **arr);
void		ft_free_cmds(t_cmd *cmds);
int			ft_heredoc(char *delimiter, int expand, t_process *proc);
void		ft_exec_error(char *path, char *cmd, int err);

#endif