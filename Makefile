# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+:+     #
#    By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        #
#                                                 +#+#+#+#+#+   +#+           #
#    Created: 2025/07/24 13:18:15 by aghergut          #+#    #+#             #
#    Updated: 2025/11/04 00:35:00 by aghergut         ###   ########.fr       #
#                                                                              #
# **************************************************************************** #


# DEBUG NOTE: Removed '-s' and '@' symbols to display all compiler errors.
# MAKEFLAGS += -s

GREEN = \033[0;92m
RED = \033[38;5;160m
RESET = \033[0m

NAME = minishell42

CC = cc 
CFLAGS = -Wall -Wextra -Werror

# ASAN Configuration
ASAN ?= 0
ifeq ($(ASAN),1)
# ASAN flags are now ONLY used for the final link step
ASAN_FLAGS = -fsanitize=address -g
else
ASAN_FLAGS =
endif

# LIBFT
LIBFT = import/libft/
MAKE_LIBFT = make -C $(LIBFT) > /dev/null 2>&1
CLEAN_LIBFT = make clean -C $(LIBFT) > /dev/null 2>&1
FCLEAN_LIBFT = make fclean -C $(LIBFT) > /dev/null 2>&1
FLAGS_LIBFT = -L$(LIBFT) -lft

INCLUDES = -I. -I$(LIBFT) 
LIBRARIES = $(FLAGS_LIBFT) -lreadline

# DIRECTORIES
BUILTINS_DIR = builtins/
HANDLERS_DIR = handlers/
UTILS_DIR = utils/
INPUT_DIR = input/
MAIN_DIR = main/
PARSE_TOKENS_DIR = $(INPUT_DIR)parse_tokens/
PROCESS_DIR = process/

OBJS_BUILTINS = $(BUILTINS_DIR)objs/
OBJS_BUILTINS_UTILS = $(BUILTINS_DIR)$(UTILS_DIR)objs/
OBJS_HANDLERS = $(HANDLERS_DIR)objs/
OBJS_UTILS = $(UTILS_DIR)objs/
OBJS_INPUT = $(INPUT_DIR)objs/
OBJS_PARSE_TOKENS = $(PARSE_TOKENS_DIR)objs/
OBJS_PARSE_TOKENS_UTILS = $(PARSE_TOKENS_DIR)$(UTILS_DIR)objs/
OBJS_PROCESS = $(PROCESS_DIR)objs/
OBJS_MAIN = $(MAIN_DIR)objs/

# SOURCES
SRCS1 = $(BUILTINS_DIR)$(UTILS_DIR)ft_cd_feats.c \
        $(BUILTINS_DIR)$(UTILS_DIR)ft_cd_utils.c \
        $(BUILTINS_DIR)$(UTILS_DIR)ft_getcwd.c \
        $(BUILTINS_DIR)$(UTILS_DIR)ft_getvar.c \
		$(BUILTINS_DIR)$(UTILS_DIR)ft_isbuiltin.c

SRCS2 = $(BUILTINS_DIR)ft_builtins.c $(BUILTINS_DIR)ft_cd.c \
        $(BUILTINS_DIR)ft_clear.c $(BUILTINS_DIR)ft_echo.c \
        $(BUILTINS_DIR)ft_exit.c $(BUILTINS_DIR)ft_export.c \
        $(BUILTINS_DIR)ft_pwd.c $(BUILTINS_DIR)ft_env.c \
        $(BUILTINS_DIR)ft_unset.c

SRCS3 = $(HANDLERS_DIR)ft_sigint.c

SRCS4 = $(INPUT_DIR)$(PARSE_TOKENS_DIR)$(UTILS_DIR)ft_inputvar_utils.c \
        $(INPUT_DIR)$(PARSE_TOKENS_DIR)$(UTILS_DIR)ft_parse_utils.c \
        $(INPUT_DIR)$(PARSE_TOKENS_DIR)$(UTILS_DIR)ft_quote_utils.c \
		$(INPUT_DIR)$(PARSE_TOKENS_DIR)$(UTILS_DIR)ft_specialvars.c \
		$(INPUT_DIR)$(PARSE_TOKENS_DIR)$(UTILS_DIR)ft_cmds_utils.c

SRCS5 = $(INPUT_DIR)$(PARSE_TOKENS_DIR)ft_inputvar.c \
        $(INPUT_DIR)$(PARSE_TOKENS_DIR)ft_parse_line.c \
        $(INPUT_DIR)$(PARSE_TOKENS_DIR)ft_parse_token.c \
        $(INPUT_DIR)$(PARSE_TOKENS_DIR)ft_quote.c \
        $(INPUT_DIR)$(PARSE_TOKENS_DIR)ft_std.c\
		$(INPUT_DIR)$(PARSE_TOKENS_DIR)ft_cmds.c

SRCS6 = $(INPUT_DIR)ft_prompt.c $(INPUT_DIR)ft_readinput.c 

SRCS7 = $(PROCESS_DIR)ft_fork_process.c \
		$(PROCESS_DIR)ft_exec_utils.c \
		$(PROCESS_DIR)ft_pipe_utils.c \
		$(PROCESS_DIR)ft_exec_redirs.c

SRCS8 = $(UTILS_DIR)ft_free.c $(UTILS_DIR)ft_init.c \
        $(UTILS_DIR)ft_clear_strtok.c $(UTILS_DIR)ft_construct.c \
        $(UTILS_DIR)ft_addspace.c $(UTILS_DIR)ft_safeadd_nodes.c\
        $(UTILS_DIR)ft_appendre.c $(UTILS_DIR)ft_heredoc.c \
        $(UTILS_DIR)ft_reinput.c $(UTILS_DIR)ft_reoutput.c \
		$(UTILS_DIR)ft_io_utils.c
        
SRCS9 = $(MAIN_DIR)main.c

# OBJECTS
OBJS =  $(SRCS1:$(BUILTINS_DIR)$(UTILS_DIR)%.c=$(OBJS_BUILTINS_UTILS)%.o) \
        $(SRCS2:$(BUILTINS_DIR)%.c=$(OBJS_BUILTINS)%.o) \
        $(SRCS3:$(HANDLERS_DIR)%.c=$(OBJS_HANDLERS)%.o) \
        $(SRCS4:$(INPUT_DIR)$(PARSE_TOKENS_DIR)$(UTILS_DIR)%.c=$(OBJS_PARSE_TOKENS_UTILS)%.o) \
        $(SRCS5:$(INPUT_DIR)$(PARSE_TOKENS_DIR)%.c=$(OBJS_PARSE_TOKENS)%.o) \
        $(SRCS6:$(INPUT_DIR)%.c=$(OBJS_INPUT)%.o) \
        $(SRCS7:$(PROCESS_DIR)%.c=$(OBJS_PROCESS)%.o) \
		$(SRCS8:$(UTILS_DIR)%.c=$(OBJS_UTILS)%.o) \
        $(SRCS9:$(MAIN_DIR)%.c=$(OBJS_MAIN)%.o) 

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE_LIBFT)
	@$(CC) $(OBJS) $(LIBRARIES) $(INCLUDES) $(ASAN_FLAGS) -o $(NAME)
	@echo "$(GREEN)Compiled successfully: $(NAME)$(RESET)"

$(OBJS_BUILTINS_UTILS)%.o: $(BUILTINS_DIR)$(UTILS_DIR)%.c
	@mkdir -p $(OBJS_BUILTINS_UTILS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(ASAN_FLAGS)-c $< -o $@

$(OBJS_BUILTINS)%.o: $(BUILTINS_DIR)%.c
	@mkdir -p $(OBJS_BUILTINS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(ASAN_FLAGS)-c $< -o $@

$(OBJS_HANDLERS)%.o: $(HANDLERS_DIR)%.c
	@mkdir -p $(OBJS_HANDLERS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(ASAN_FLAGS)-c $< -o $@

$(OBJS_PARSE_TOKENS_UTILS)%.o: $(PARSE_TOKENS_DIR)$(UTILS_DIR)%.c
	@mkdir -p $(OBJS_PARSE_TOKENS_UTILS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(ASAN_FLAGS)-c $< -o $@

$(OBJS_PARSE_TOKENS)%.o: $(PARSE_TOKENS_DIR)%.c
	@mkdir -p $(OBJS_PARSE_TOKENS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(ASAN_FLAGS)-c $< -o $@

$(OBJS_INPUT)%.o: $(INPUT_DIR)%.c
	@mkdir -p $(OBJS_INPUT)
	@$(CC) $(CFLAGS) $(INCLUDES) $(ASAN_FLAGS)-c $< -o $@

$(OBJS_PROCESS)%.o: $(PROCESS_DIR)%.c
	@mkdir -p $(OBJS_PROCESS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(ASAN_FLAGS)-c $< -o $@

$(OBJS_UTILS)%.o: $(UTILS_DIR)%.c
	@mkdir -p $(OBJS_UTILS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(ASAN_FLAGS)-c $< -o $@

$(OBJS_MAIN)%.o: $(MAIN_DIR)%.c
	@mkdir -p $(OBJS_MAIN)
	@$(CC) $(CFLAGS) $(INCLUDES) $(ASAN_FLAGS)-c $< -o $@

clean:
	@rm -Rf $(OBJS_BUILTINS_UTILS) $(OBJS_BUILTINS) $(OBJS_HANDLERS)
	@rm -Rf $(OBJS_PARSE_TOKENS) $(OBJS_PARSE_TOKENS_UTILS)
	@rm -Rf $(OBJS_INPUT) $(OBJS_UTILS) $(OBJS_MAIN) $(OBJS_PROCESS)
	@$(CLEAN_LIBFT)
	@echo "$(GREEN)Object files removed$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@$(FCLEAN_LIBFT)
	@echo "$(GREEN)Executable $(NAME) removed$(RESET)"

re: fclean all

.PHONY: all clean fclean re
