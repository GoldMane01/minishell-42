# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/16 19:36:42 by crmunoz-          #+#    #+#              #
#    Updated: 2024/12/16 19:37:23 by crmunoz-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := minishell
CC        := gcc
FLAGS    := -g -lreadline -Wall -Wextra -Werror 
################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS        :=      minishell.c \
                          builtins/ft_exit.c \
                          builtins/builtins_first.c \
                          builtins/builtins_second.c \
                          builtins/check_built.c \
                          utils/path.c \
                          utils/fd.c \
                          utils/cmd.c \
                          utils/signals.c \
                          utils/parsing.c \
                          utils/utils.c \
                          utils/pipex.c \
                          utils/env.c \
                          utils/free.c \
                          utils/init.c \
                          utils/expand.c \
                          utils/splitting.c \
                          utils/quotes.c \
                          utils/args.c \
                          utils/redir.c \
                          lib/ft_strnstr.c \
                          lib/ft_split.c \
                          lib/ft_substr.c \
                          lib/ft_itoa.c \
                          lib/ft_isspace.c \
                          lib/ft_strdup.c \
                          lib/ft_strlcat.c \
                          lib/ft_strchr.c \
                          lib/ft_lstlast.c \
                          lib/ft_strcmp.c \
                          lib/ft_strlcpy.c \
                          lib/ft_isalun.c \
                          lib/ft_strjoin.c \
                          lib/ft_strlen.c \
                          lib/ft_lstsize.c \
                          
OBJS        := $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

################################################################################
#                                  Makefile  objs                              #
################################################################################


CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f

${NAME}:	${OBJS}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			${CC} ${FLAGS} -o ${NAME} ${OBJS} -lreadline
			@echo "$(GREEN)$(NAME) created[0m ✔️"

all:		${NAME}

bonus:		all

clean:
			@ ${RM} *.o */*.o */*/*.o
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:		clean
			@ ${RM} ${NAME}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:			fclean all

.PHONY:		all clean fclean re


