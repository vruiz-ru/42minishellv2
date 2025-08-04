/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:49:41 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/04 22:27:00 by aghergut         ###   ########.fr       */
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

typedef struct Main_program
{
	char	*prompt;
	char	*line;
	char	*name;
	char	**sh_envp;
	int     status;
	bool	running;
	bool	sigint_received;
}	t_main;

typedef struct Builtins
{
	t_list	*tokens;
	bool	flags;
	bool	in_file;
	bool	out_file;
	bool	single_quotes;
	bool	double_quotes;
}	t_builts;

typedef struct Subprocess
{
	char		**local_env;
	char		**buffer_env;
	t_builts	*builtins;
	char		*line;
	char		*prompt;
	int			exit_status;
	t_main		*ptr_main;
}   t_subproc;


// INIT
int 	init_subproc(t_main *shell, t_subproc **sub);
int		init_main(t_main **shell, char *name, char *envp[]);
int		init_builtins(t_builts **builts);
// UTILS
void	free_main(t_main *shell);
void	free_builts(t_builts *builtins);
void	free_subprocess(t_subproc *ptr);
char	*ft_getvar(char **envp, char *var_name);
void	ft_appendre(t_subproc *process);
void	ft_heredoc(t_subproc *process);
int		ft_reinput(t_subproc *process);
int		ft_reoutput(t_subproc *process);
int		ft_dquotes(t_subproc *process, char *token);
int		ft_squotes(t_subproc *process, char *token);
// BUILTINS
int		ft_builtins(t_subproc *process);
int     ft_cd(t_subproc *process);
void	ft_clear(void);
int	    ft_echo(t_subproc *process);
int		ft_exit(t_subproc *process);
int 	ft_export(t_subproc *process);
char	*ft_getcwd(void);
int 	ft_pwd(t_subproc *process);
int		ft_getenv(t_subproc *process);
int		ft_unset(t_subproc **process);
// HANDLERS
void	handle_sigint(int sig);
// READINPUT
int		ft_readinput(t_subproc *proc);
char	*ft_content(t_subproc *process, char *token);

#endif