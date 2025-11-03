# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/22 13:11:03 by aghergut          #+#    #+#              #
#    Updated: 2025/11/03 21:30:04 by aghergut         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
CFLAGS = -Wall -Werror -Wextra -fPIE

NAME = libft.a

# Define folders for different parts of the library
CHANGECHAR_DIR = changechar/
CHECKCHAR_DIR = checkchar/
STRTOINT_DIR = strtoint/
GET_NEXT_LINE_DIR = get_next_line/
STRINGS_DIR = strings/
MAPS_DIR = maps/
MEMORY_DIR = memory/
PUTS_DIR = puts/
LISTS_DIR = lists/
FTPRINTF_DIR = ft_printf/

# Source files for each module
SRCS0 =	$(CHANGECHAR_DIR)ft_tolower.c $(CHANGECHAR_DIR)ft_toupper.c
SRCS1 = $(CHECKCHAR_DIR)ft_isalnum.c $(CHECKCHAR_DIR)ft_isascii.c \
		$(CHECKCHAR_DIR)ft_isalpha.c $(CHECKCHAR_DIR)ft_isdigit.c \
		$(CHECKCHAR_DIR)ft_isprint.c
SRCS2 = $(STRTOINT_DIR)ft_atoi.c $(STRTOINT_DIR)ft_itoa.c
SRCS3 = $(GET_NEXT_LINE_DIR)get_next_line.c
SRCS4 = $(STRINGS_DIR)ft_strchr.c $(STRINGS_DIR)ft_strlcat.c \
	  	$(STRINGS_DIR)ft_strlcpy.c $(STRINGS_DIR)ft_strlen.c \
		$(STRINGS_DIR)ft_strncmp.c $(STRINGS_DIR)ft_strnstr.c \
	  	$(STRINGS_DIR)ft_strrchr.c $(STRINGS_DIR)ft_strtrim.c \
		$(STRINGS_DIR)ft_substr.c $(STRINGS_DIR)ft_strjoin.c \
	  	$(STRINGS_DIR)ft_split.c $(STRINGS_DIR)ft_strdup.c \
	  	$(STRINGS_DIR)ft_strmapi.c $(STRINGS_DIR)ft_strncat.c \
	  	$(STRINGS_DIR)ft_striteri.c $(STRINGS_DIR)ft_calloc.c \
	  	$(STRINGS_DIR)ft_bzero.c $(STRINGS_DIR)ft_strtok.c \
		$(STRINGS_DIR)ft_strjoin_free.c $(STRINGS_DIR)ft_addchar.c
SRCS5 = $(MEMORY_DIR)ft_memset.c $(MEMORY_DIR)ft_memcpy.c \
	  	$(MEMORY_DIR)ft_memmove.c $(MEMORY_DIR)ft_memchr.c \
	  	$(MEMORY_DIR)ft_memcmp.c
SRCS6 = $(PUTS_DIR)ft_putchar_fd.c $(PUTS_DIR)ft_putstr_fd.c \
	  	$(PUTS_DIR)ft_putendl_fd.c $(PUTS_DIR)ft_putnbr_fd.c \
	  	$(PUTS_DIR)ft_putuint.c
SRCS7 = $(LISTS_DIR)ft_lstnew.c $(LISTS_DIR)ft_lstadd_front.c \
	  	$(LISTS_DIR)ft_lstsize.c $(LISTS_DIR)ft_lstlast.c \
	  	$(LISTS_DIR)ft_lstadd_back.c $(LISTS_DIR)ft_lstdelone.c \
	  	$(LISTS_DIR)ft_lstclear.c $(LISTS_DIR)ft_lstiter.c \
	  	$(LISTS_DIR)ft_lstmap.c
SRCS8 = $(FTPRINTF_DIR)ft_fill.c $(FTPRINTF_DIR)ft_flagadd.c \
		$(FTPRINTF_DIR)ft_flagalt.c $(FTPRINTF_DIR)ft_flagsign.c \
		$(FTPRINTF_DIR)ft_flagspace.c $(FTPRINTF_DIR)ft_gethex.c \
		$(FTPRINTF_DIR)ft_memlen.c $(FTPRINTF_DIR)ft_numlen.c \
		$(FTPRINTF_DIR)ft_printchar.c $(FTPRINTF_DIR)ft_printstr.c  \
		$(FTPRINTF_DIR)ft_printint.c  $(FTPRINTF_DIR)ft_printu.c  \
		$(FTPRINTF_DIR)ft_printpxx.c $(FTPRINTF_DIR)ft_printf.c
SRCS9 =	$(MAPS_DIR)ft_mapitem_del.c $(MAPS_DIR)ft_mapdup.c $(MAPS_DIR)ft_map_utils.c \
		$(MAPS_DIR)ft_mapfree.c $(MAPS_DIR)ft_mapitem_index.c \
		$(MAPS_DIR)ft_mapitem_replace.c $(MAPS_DIR)ft_mapsize.c \
		$(MAPS_DIR)ft_mapitem_add.c $(MAPS_DIR)ft_mapnew.c

# Object directories
OBJS_DIR_CHANGECHAR = $(CHANGECHAR_DIR)o_files/
OBJS_DIR_CHECKCHAR = $(CHECKCHAR_DIR)o_files/
OBJS_DIR_STRTOINT = $(STRTOINT_DIR)o_files/
OBJS_DIR_GET_NEXT_LINE = $(GET_NEXT_LINE_DIR)o_files/
OBJS_DIR_STRINGS = $(STRINGS_DIR)o_files/
OBJS_DIR_MAPS = $(MAPS_DIR)o_files/
OBJS_DIR_MEMORY = $(MEMORY_DIR)o_files/
OBJS_DIR_PUTS = $(PUTS_DIR)o_files/
OBJS_DIR_LISTS = $(LISTS_DIR)o_files/
OBJS_DIR_FTPRINTF = $(FTPRINTF_DIR)o_files/

# Object files with correct paths
OBJS =  $(SRCS0:$(CHANGECHAR_DIR)%.c=$(OBJS_DIR_CHANGECHAR)%.o) \
        $(SRCS1:$(CHECKCHAR_DIR)%.c=$(OBJS_DIR_CHECKCHAR)%.o) \
        $(SRCS2:$(STRTOINT_DIR)%.c=$(OBJS_DIR_STRTOINT)%.o) \
        $(SRCS3:$(GET_NEXT_LINE_DIR)%.c=$(OBJS_DIR_GET_NEXT_LINE)%.o) \
        $(SRCS4:$(STRINGS_DIR)%.c=$(OBJS_DIR_STRINGS)%.o) \
        $(SRCS5:$(MEMORY_DIR)%.c=$(OBJS_DIR_MEMORY)%.o) \
        $(SRCS6:$(PUTS_DIR)%.c=$(OBJS_DIR_PUTS)%.o) \
        $(SRCS7:$(LISTS_DIR)%.c=$(OBJS_DIR_LISTS)%.o) \
        $(SRCS8:$(FTPRINTF_DIR)%.c=$(OBJS_DIR_FTPRINTF)%.o) \
        $(SRCS9:$(MAPS_DIR)%.c=$(OBJS_DIR_MAPS)%.o)

INCLUDES = -I.

# Default target
all: $(NAME)

# Create the library
$(NAME): $(OBJS)
	@ar -rcs $(NAME) $(OBJS)
	@echo "$(NAME) created successfully!"

# Create object directories and compile
$(OBJS_DIR_CHANGECHAR)%.o: $(CHANGECHAR_DIR)%.c
	@mkdir -p $(OBJS_DIR_CHANGECHAR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR_CHECKCHAR)%.o: $(CHECKCHAR_DIR)%.c
	@mkdir -p $(OBJS_DIR_CHECKCHAR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR_STRTOINT)%.o: $(STRTOINT_DIR)%.c
	@mkdir -p $(OBJS_DIR_STRTOINT)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR_GET_NEXT_LINE)%.o: $(GET_NEXT_LINE_DIR)%.c
	@mkdir -p $(OBJS_DIR_GET_NEXT_LINE)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR_STRINGS)%.o: $(STRINGS_DIR)%.c
	@mkdir -p $(OBJS_DIR_STRINGS)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR_MEMORY)%.o: $(MEMORY_DIR)%.c
	@mkdir -p $(OBJS_DIR_MEMORY)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR_PUTS)%.o: $(PUTS_DIR)%.c
	@mkdir -p $(OBJS_DIR_PUTS)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR_LISTS)%.o: $(LISTS_DIR)%.c
	@mkdir -p $(OBJS_DIR_LISTS)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR_FTPRINTF)%.o: $(FTPRINTF_DIR)%.c
	@mkdir -p $(OBJS_DIR_FTPRINTF)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR_MAPS)%.o: $(MAPS_DIR)%.c
	@mkdir -p $(OBJS_DIR_MAPS)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean rule to remove object files
clean:
	@rm -Rf */o_files
	@echo "Object files removed successfully\n"
# Full clean rule
fclean: clean
	@rm -f $(NAME)
	@echo "Program removed successfully\n"

# Rebuild the project
re: fclean all

.PHONY: all clean fclean re