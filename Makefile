# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/24 13:18:15 by aghergut          #+#    #+#              #
#    Updated: 2025/07/25 14:00:56 by aghergut         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += -s

TARGET= minishell

CC= cc
CGLAGS= -Werror -Wextra -Wall
INCLUDES= -I. -Llibft -lft -lreadline

SRCS= frees.c prompt.c get_cwd.c get_env.c get_variable.c signals.c main.c

OBJS_DIR = objs/
OBJS=$(SRCS:%.c=$(OBJS_DIR)%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	@make -C libft
	@$(CC) $(SRCS) $(INCLUDES) -o $(TARGET)
	@echo "Done minishell."

$(OBJS_DIR)%.o: %.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -Rf $(OBJS_DIR)

fclean: clean
	@rm -f $(TARGET)

re: fclean all

iPHONY: all clean fclean re
