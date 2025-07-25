#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <limits.h>

#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>


#define PROMPT		" 👉 "
#define REPLY	"💬"
#define WRONG		"❓"

#define CLEAR	"\e[1;1H\e[2J"	// \033[H\033[J"

// char    *current_prompt(char *cwd);

char	*get_prompt(void);
char	*get_variable(char *envp[], char *var_name);
char	*get_cwd(char *flags);
void	get_env(char *envp[]);

void handle_sigint(int sig);

void	free_map(char **map);
#endif