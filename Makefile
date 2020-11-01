# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/17 00:51:07 by ommadhi           #+#    #+#              #
#    Updated: 2020/11/01 06:01:40 by ysarsar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =  src/builtins.c\
	   	src/environement.c\
	   	src/execute_pipe.c\
	   	src/execute_redirection.c\
	   	src/execute_redirection2.c\
	   	src/execute_simple_cmd.c\
	   	src/ft_cd.c\
	   	src/ft_cd_env.c\
	   	src/ft_change_arg.c\
	   	src/main.c\
	   	src/path_checker.c\
	   	src/sh_execution.c\
	   	src/sh_loop.c\
	   	src/tools.c\
	   	src/tools2.c\
		src/ft_expanitions.c\
		src/free_ast.c\
		src/parser/check_quotes.c\
	   	src/parser/check_syntax.c\
	   	src/parser/parse_types.c\
	   	src/parser/parser.c\
	   	src/parser/tokenz.c\
	   	src/parser/tokenz_checker.c\
		src/parser/tokenz_checker2.c\
		src/hashtable/hashtable.c\
		src/hashtable/hash_tools.c\
		src/hashtable/flags.c\
		src/hashtable/errors_print.c\
		src/hashtable/h_tools.c\
		src/hashtable/hash_tools2.c\


OBJS    = $(SRCS:.c=.o)


NAME		= 21sh
CC = gcc
CFLAGS		= -Wall -Wextra

all : $(NAME)

$(NAME) : $(OBJS)
	@echo "project under construction"
	@make -s -C libft
	@gcc -g $(CFLAG) $(OBJS) libft/libft.a -o $(NAME) -lreadline

clean :
	@rm -rf $(OBJS) 
	@make -s -C libft clean

fclean : clean
	@rm -rf $(NAME)
	@make -s -C libft fclean

re : fclean all
