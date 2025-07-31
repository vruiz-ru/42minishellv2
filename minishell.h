/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:49:41 by aghergut          #+#    #+#             */
/*   Updated: 2025/07/31 21:23:24 by aghergut         ###   ########.fr       */
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


#define PROMPT		" 👉 "
#define REPLY	"💬"
#define WRONG		"❓"

#define CLEAR	"\e[1;1H\e[2J"	// \033[H\033[J"

typedef struct Shell_utils
{
	char	**tokens;
	char	*line;
	char	*prompt;
	char	*buffer_var;
	char	*home_path;
	bool	running;
}	t_utils;

// UTILS
void	free_map(char **map);
void	free_main(t_utils *main);
char	*ft_getvar(char *envp[], char *var_name);
int		is_variable(char *envp[], char *var_name);
char	*ft_prompt(void);
int		ft_readinput(t_utils **main);
// BUILTINS
int		ft_builtins(t_utils *main_struct, char *envp[]);
int     ft_cd(t_utils *main_struct);
void	ft_clear(void);
int	    ft_echo(t_utils *main_struct, char *envp[]);
int		ft_exit(t_utils *main_struct);
int 	ft_export(t_utils *main_struct, char *envp[]);
char	*ft_getcwd(char *flags);
int		ft_getenv(char *envp[]);
int		ft_unset(t_utils *main_struct, char *envp[]);
// HANDLERS
void	handle_sigint(int sig);


#endif