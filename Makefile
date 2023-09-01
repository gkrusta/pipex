# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/01 11:07:54 by gkrusta           #+#    #+#              #
#    Updated: 2023/09/01 12:19:50 by gkrusta          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = gcc
FLAGS = -Wall -Wextra -Werror -g

LIBFT = libft/libft.a
HEADERS = -I ./inc -I ./libft


SRCS =  $(wildcard src/*.c)

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME) 

$(NAME): $(OBJS)
	@ echo "\033[32mCompiling Pipex...\n"
	@$(CC) $(FLAGS) $(OBJS) $(LIBFT) $(HEADERS) -o $@
	@ echo "\n\t\t\033[32mCompiled!\n"

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@ $(HEADERS)

$(LIBFT):
	@ make -C libft/ all
	@ echo "\n\t\t\033[32mCreated libft!\n"

RM = rm -f

clean:
	@ $(RM) $(OBJS) 
	@ make -C libft/ clean
	@ echo "\n\t\t\033[32mEverything is clean!\n"

fclean: clean
	@ $(RM) $(NAME)
	@ make -C libft fclean

re: fclean all

.PHONY: all clean fclean re