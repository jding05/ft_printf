# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sding <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/08 17:05:59 by sding             #+#    #+#              #
#    Updated: 2018/04/10 17:18:39 by sding            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKE = make -C
NAME = libftprintf.a
LIB = src/libft/
FLAGS = -Wall -Wextra -Werror
CC = gcc
HEADER = -I /includes

#When compiling. you need to add your .a lib
CFILES =		src/dispatch_table.c\
				src/parse.c\
				src/ft_printf.c\
				src/initial_print.c\
				src/handle_int.c\
				src/handle_char.c\
				src/handle_wchar.c\
				src/handle_str.c\
				src/handle_wstr.c\
				src/handle_hex.c\
				src/handle_ptr.c\
				src/handle_octal.c\
				src/handle_unsigned.c\
				src/handle_escape.c\
				src/get_int_type.c

#These options are here in case the lib needs to be recompiled.
#LIBM, LIBC, LIBF will run rules re, clean and fclean inside the libft folder
LIBM = $(MAKE) $(LIB)
LIBR = $(MAKE) $(LIB) re
LIBC = $(MAKE) $(LIB) clean
LIBF = $(MAKE) $(LIB) fclean
OBJECTS = $(CFILES:.c=.o)
OBJ_DIR = objects

DFLAGS = $(CFLAGS) -g $(LIBD) $(CFILES) -o
DNAME = $(NAME)_debug
DOBJS = $(CFILES:.c = .o)
# export DRAGS=01.map
all: $(NAME)

$(NAME):
	@$(LIBM)
	@$(CC) $(FLAGS) -c $(CFILES) $(Header)
	@cp src/libft/libft.a $(NAME)
	@ar rcs $(NAME) *.o
	@ranlib $(NAME)
	@mkdir $(OBJ_DIR)
	@mv *.o $(OBJ_DIR)
	@echo "\033[33mLib File \"libftprintf.a\" Created\033[0m"

clean:
	@$(LIBC)
	@/bin/rm -rf $(OBJ_DIR)
	@echo "\033[31mft_printf Object File Removed\033[0m"

fclean:
	@$(LIBF)
	@/bin/rm -f $(NAME) *.a
	@/bin/rm -rf $(OBJ_DIR)
	@rm -rf $(NAME)
	@rm -f $(DNAME)
	@rm -rf $(DNAME).dSYM
	@echo "\033[31mft_printf: Removed exacutable & .o files\033[0m"

re: fclean all



debug: $(DNAME)

$(DNAME): fclean
	@$(LIBM)
	$(CC) $(DFLAGS) $(DNAME)
	# lldb $(DNAME) $(DARGS)

# tell Make that they're not associated with files
.PHONY: all clean fclean re debug
