/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:49:41 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/02 21:01:53 by aghergut         ###   ########.fr       */
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

#define PROMPT_ARROW	" 👉 "
#define PROMPT_HOME		"minishell:~ 👉 "
#define HOME	"~"
#define REPLY	"💬"
#define WRONG	"❓"
#define NAME	"minishell42"
#define CLEAR	"\e[1;1H\e[2J"	// \033[H\033[J

typedef struct Main_program
{
	char	*prompt;
	char	*line;
	char	*name;
	char	*home_path;
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
	char		*current_wd;
	char		*last_wd;
	int			exit_status;
	t_main		*ptr_main;
}   t_subproc;


// INIT
int 	init_subproc(t_main *shell, t_subproc **sub);
int		init_main(t_main **shell, char *name, char *envp[]);
int		init_builtins(t_builts **builts);
// UTILS
int 	path_input(t_subproc *process);
int		invalid_options(char *token);
void	ft_setpaths(t_subproc *process);
int		dash_feature(t_subproc *process);
int		up_feature(t_subproc *process);
int		home_feature(t_subproc *process);
int		back_feature(t_subproc *process);
int		root_feature(t_subproc *process);
void	free_main(t_main *shell);
void	free_builts(t_builts *builtins);
void	free_subprocess(t_subproc *ptr);
char	*ft_getvar(char **envp, char *var_name);
char	*ft_prompt(t_subproc *process);
void	ft_appendre(t_subproc *process);
void	ft_heredoc(t_subproc *process);
int		ft_reinput(t_subproc *process);
int		ft_reoutput(t_subproc *process);
char	*ft_getcwd(void);
// BUILTINS
int		ft_builtins(t_subproc *process);
void	ft_clear(void);
int		ft_exit(t_subproc *process);
int 	ft_export(t_subproc *process);
int 	ft_pwd(t_subproc *process);
int		ft_getenv(t_subproc *process);
int		ft_unset(t_subproc **process);
int		ft_echo(t_subproc *process);
int		ft_cd(t_subproc *process);
// HANDLERS
void	handle_sigint(int sig);
// READINPUT
int		ft_getquote_idx(char *token, char type);
int		ft_checkpair(char *str, char ch);
char	*ft_quotes_token(t_list *tokens, char *line, char ch);
int		ft_create_tokens(t_subproc *process);
// int		ft_parse_tokens(t_subproc *process);
int		ft_readinput(t_subproc *proc);

#endif