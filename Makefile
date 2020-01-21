# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/21 15:30:32 by ibaali            #+#    #+#              #
#    Updated: 2020/01/21 15:33:41 by ibaali           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC= parce.h

LIBOBJ = 	ft_atoi.o				\
			ft_bzero.o				\
			ft_calloc.o				\
			ft_isalnum.o			\
			ft_isalpha.o			\
			ft_isascii.o			\
			ft_isdigit.o			\
			ft_isprint.o			\
			ft_itoa.o				\
			ft_memccpy.o			\
			ft_memchr.o				\
			ft_memcmp.o				\
			ft_memmove.o			\
			ft_memset.o				\
			ft_putchar_fd.o			\
			ft_putendl_fd.o			\
			ft_putnbr_fd.o			\
			ft_putstr_fd.o			\
			ft_split.o				\
			ft_strchr.o				\
			ft_strdup.o				\
			ft_strjoin.o			\
			ft_strlcat.o			\
			ft_strlcpy.o			\
			ft_strlen.o				\
			ft_strmapi.o			\
			ft_strncmp.o			\
			ft_strnstr.o			\
			ft_strrchr.o			\
			ft_strtrim.o			\
			ft_substr.o				\
			ft_tolower.o			\
			ft_toupper.o			\
			ft_memcpy.o

LIB = libft.a
LIBMAKEFILE = libft/Makefile
CC = gcc
FLAGS = -fsanitize=address -g
NAME = minishell

all: $(NAME)

$(NAME):
	@make -f $(LIBMAKEFILE)
	@$(CC) $(FLAGS)

clean:
	@rm -rf $(LIBOBJ)
	@make fclean -f $(LIBMAKEFILE)
	@rm -rf $(NAME)

fclean: clean
	@rm -rf $(NAME)
	@rm -rf echo pwd cd

re: fclean all

.PHONY: re clean all fclean