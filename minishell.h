/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:49:41 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/01 20:52:15 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "import/libft/libft.h"

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <limits.h>
#include <stdbool.h>

#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

#define PROMPT		"minishell:"
#define PROMPT_ARROW	" 👉 "
#define PROMPT_HOME		"minishell:~ 👉 "
#define REPLY	"💬"
#define WRONG	"❓"
#define NAME	"minishell42"
#define CLEAR	"\e[1;1H\e[2J"	// \033[H\033[J"

typedef struct Builtins
{
	t_list	*tokens;
	bool	flags;
	bool	in_file;
	bool	out_file;
	bool	single_quotes;
	bool	double_quotes;
}	t_builts;

typedef struct Shell_utils
{
	t_builts	*builtins;
	char		*prompt;
	char		*line;
	char		*name;
	char		**sh_envp;
	bool		running;
	bool		sigint_received;
}	t_utils;

// UTILS
void	free_main(t_utils *main);
char	*ft_getvar(char *envp[], char *var_name);
int		is_variable(char *envp[], char *var_name);
int		ft_readinput(t_utils *main);
// BUILTINS
int		ft_builtins(t_utils *main_struct, char *envp[]);
int     ft_cd(t_utils *main_struct);
void	ft_clear(void);
int	    ft_echo(t_utils *main_struct, char *envp[]);
int		ft_exit(t_utils *main_struct);
int 	ft_export(t_utils *main_struct, char *envp[]);
char	*ft_getcwd(void);
int 	ft_pwd(t_utils *shell);
int		ft_getenv(char *envp[]);
int		ft_unset(t_utils *main_struct, char *envp[]);
// HANDLERS
void	handle_sigint(int sig);


#endif