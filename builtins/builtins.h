/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:47:46 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/09 16:54:01 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../headers/macros.h"
# include "../headers/minishell.h"
# include "../headers/structs.h"
# include "../import/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>

// BUITLINS/UTILS
//      CD
int		dash_feature(t_process *process, t_cmd *cmd);
int		up_feature(t_process *process, t_cmd *cmd);
int		home_feature(t_process *process, t_cmd *cmd);
int		back_feature(t_process *process, t_cmd *cmd);
int		root_feature(t_process *process, t_cmd *cmd);
void	ft_setpaths(t_process *process);
void	update_logical_parent(t_process *process);
int		invalid_options(char *token);
int		path_input(t_process *process, t_cmd *cmd);
char	*ft_getcwd(void);
char	*ft_getvar(char **envp, char *var_name);
int		ft_is_parent_builtin(t_cmd *cmd);
// COMMANDS
int		ft_builtins(t_process *process, t_cmd *cmd);
int		ft_echo(t_process *process, t_cmd *cmd);
int		ft_cd(t_process *process, t_cmd *cmd);
int		ft_pwd(t_process *process, t_cmd *cmd);
int		ft_env(t_process *process, t_cmd *cmd);
int		ft_export(t_process *process, t_cmd *cmd);
int		ft_unset(t_process *process, t_cmd *cmd);
int		ft_exit(t_process *process, t_cmd *cmd);
int		ft_clear(t_process *process, t_cmd *cmd);

#endif