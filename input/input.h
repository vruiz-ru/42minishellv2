/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:15:56 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/09 17:57:30 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

#include "../headers/macros.h"
#include "../headers/structs.h"
#include "../headers/minishell.h"
#include "../import/libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>

// READINPUT
char	*ft_prompt(t_process *process);
void	ft_readinput(t_process *process);
// PARSE_TOKENS/UTILS
//		INPUTVAR
int		already_exists(char **env, char *var_name);
int		add_variable(char ***map, char *item);
int		contains_variable(char *token);
int 	ft_specialvars(t_process *proc, char **var_name, char ch);
int 	return_value(t_process *process, char *line);
//      PARSE
char	*clean_line(char *content, char token);
void	scan_char(t_process *process, char *content, char **var_name, int *idx);
void	insert_value(t_process *process, char **dest, char *var_name);
int		is_var_start(char c);
int     check_ansi_quote(char *line, int idx, char delim);
//		QUOTE
char	quote_delimiter(char *line);
int		quote_pos(char *str, char delim, int times);
int 	quotes_left(char *line_left);
int 	first_occurrence(t_process *process, char *line, char delim);
// PARSE_TOKENS
int		ft_inputvar(t_process *process, char **line);
int		ft_parse_line(t_process *process);
char	*ft_parse_token(t_process *process, char *content, char token);
int		ft_quote(t_process *process, char *line);
int		ft_std(t_process *process, char *line);
#endif
