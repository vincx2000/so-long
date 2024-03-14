# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vgomes <vgomes@student.42lausanne.ch>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/24 14:09:22 by vgomes            #+#    #+#              #
#    Updated: 2024/03/14 10:37:04 by vgomes           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES 	   = ft_printf_utils.c \
			 ft_printf.c \
			 ft_print_hex.c \

			 
Compiler	= gcc

CmpFlags	= -Wall -Wextra -Werror

OFILES	= $(FILES:%.c=%.o)

NAME	= libftprintf.a

%.o: %.c
	$(Compiler) $(CmpFlags) -c $< -I ft_printf.h -o $@

$(NAME): $(OFILES)
	ar rcs libftprintf.a $(OFILES)

all: $(NAME)

clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re