/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:11:10 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/09 13:52:02 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "../import/libft/lists/lists.h"
# include <stdbool.h>

typedef struct s_environment_utils
{
	char			**parent_env;
	char			**static_env;
}					t_envs;

typedef struct s_prompt_utils
{
	char			*display;
	char			*shell_name;
	char			*home_path;
	char			*current_wd;
	char			*last_wd;
}					t_prompt;

typedef enum e_io_type
{
	IO_IN,
	IO_OUT,
	IO_APPEND,
	IO_HEREDOC
}					t_io_type;

typedef struct s_io
{
	t_io_type		type;
	char			*path;
	int				fd;
}					t_io;

typedef struct s_cmd
{
	char			**args;
	char			*path;
	t_list			*redirs;

	struct s_cmd	*next;
}					t_cmd;

typedef struct s_process_utils
{
	t_prompt		*prompt;
	t_envs			*envs;
	t_list			*tokens;
	t_cmd			*commands;
	pid_t			pid;
	char			*line;
	int				status;
	int				forks;
	bool			is_special;
	bool			is_variable;
	bool			in_heredoc;
}					t_process;

#endif