# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/24 13:18:15 by aghergut          #+#    #+#              #
#    Updated: 2025/10/04 12:41:30 by aghergut         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


MAKEFLAGS += -s

GREEN = \033[0;92m
RED = \033[38;5;160m
RESET = \033[0m

NAME = minishell42

CC = cc
CFLAGS = -Wall -Wextra -Werror

# LIBFT
LIBFT = import/libft/
MAKE_LIBFT = @make -C $(LIBFT) > /dev/null 2>&1
CLEAN_LIBFT = @make clean -C $(LIBFT) > /dev/null 2>&1
FCLEAN_LIBFT = @make fclean -C $(LIBFT) > /dev/null 2>&1
FLAGS_LIBFT = -L$(LIBFT) -lft

INCLUDES = -I. -I$(LIBFT) $(FLAGS_LIBFT) -lreadline

# DIRECTORIES
BUILTINS_DIR = builtins/
HANDLERS_DIR = handlers/
UTILS_DIR = utils/
READINPUT_DIR = readinput/
MAIN_DIR = main/

OBJS_BUILTINS = $(BUILTINS_DIR)objs/
OBJS_HANDLERS = $(HANDLERS_DIR)objs/
OBJS_UTILS = $(UTILS_DIR)objs/
OBJS_READINPUT = $(READINPUT_DIR)objs/
OBJS_MAIN = $(MAIN_DIR)objs/

# SOURCES
SRCS1 =	$(BUILTINS_DIR)ft_builtins.c $(BUILTINS_DIR)ft_cd.c \
		$(BUILTINS_DIR)ft_clear.c $(BUILTINS_DIR)ft_echo.c \
		$(BUILTINS_DIR)ft_exit.c $(BUILTINS_DIR)ft_export.c \
		$(BUILTINS_DIR)ft_pwd.c $(BUILTINS_DIR)ft_getenv.c \
		$(BUILTINS_DIR)ft_unset.c

SRCS2 = $(READINPUT_DIR)ft_utils.c $(READINPUT_DIR)ft_create_tokens.c \
		$(READINPUT_DIR)ft_parse_tokens.c $(READINPUT_DIR)ft_readinput.c

SRCS3 =	$(HANDLERS_DIR)ft_sigint.c

SRCS4 =	$(UTILS_DIR)ft_free.c $(UTILS_DIR)ft_getvar.c \
		$(UTILS_DIR)ft_init.c $(UTILS_DIR)ft_getcwd.c \
		$(UTILS_DIR)ft_cd_feats.c $(UTILS_DIR)ft_cd_utils.c \
		$(UTILS_DIR)ft_appendre.c $(UTILS_DIR)ft_heredoc.c \
		$(UTILS_DIR)ft_reinput.c $(UTILS_DIR)ft_reoutput.c \
		$(UTILS_DIR)ft_prompt.c 

SRCS5 =	$(MAIN_DIR)main.c

# OBJECTS
OBJS =	$(SRCS1:$(BUILTINS_DIR)%.c=$(OBJS_BUILTINS)%.o) \
		$(SRCS2:$(READINPUT_DIR)%.c=$(OBJS_READINPUT)%.o) \
		$(SRCS3:$(HANDLERS_DIR)%.c=$(OBJS_HANDLERS)%.o) \
		$(SRCS4:$(UTILS_DIR)%.c=$(OBJS_UTILS)%.o) \
		$(SRCS5:$(MAIN_DIR)%.c=$(OBJS_MAIN)%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE_LIBFT)
	@$(CC) $(OBJS) $(INCLUDES) -o $(NAME)
	@echo "$(GREEN)Compiled successfully: $(NAME)$(RESET)"

$(OBJS_BUILTINS)%.o: $(BUILTINS_DIR)%.c
	@mkdir -p $(OBJS_BUILTINS)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_HANDLERS)%.o: $(HANDLERS_DIR)%.c
	@mkdir -p $(OBJS_HANDLERS)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_UTILS)%.o: $(UTILS_DIR)%.c
	@mkdir -p $(OBJS_UTILS)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_READINPUT)%.o: $(READINPUT_DIR)%.c
	@mkdir -p $(OBJS_READINPUT)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_MAIN)%.o: $(MAIN_DIR)%.c
	@mkdir -p $(OBJS_MAIN)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJS_BUILTINS) $(OBJS_HANDLERS) $(OBJS_UTILS) $(OBJS_MAIN) $(OBJS_READINPUT)
	@$(CLEAN_LIBFT)
	@echo "$(GREEN)Object files removed$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@$(FCLEAN_LIBFT)
	@echo "$(GREEN)Executable $(NAME) removed$(RESET)"

re: fclean all

.PHONY: all clean fclean re