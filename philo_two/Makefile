# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: greed <greed@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2020/09/09 16:13:15 by greed         #+#    #+#                  #
#    Updated: 2020/09/09 16:14:07 by greed         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME			=	philo_two

ifeq				($(shell uname), Linux)
	CXX = gcc
else
	CXX = clang
endif
FILES			=	src/philo.c\
					src/main.c\
					src/threads.c\
					src/time.c\
					src/ultis.c\
					src/parsing.c
OBJ				=	$(FILES:.c=.o)
FLAGS		=	-Wall -Wextra -Werror -O3
INCLUDES	=	-I includes
# COLORS
WHITE   = \x1b[37;01m
CYAN    = \x1b[36;01m
PINK    = \x1b[35;01m
BLUE    = \x1b[34;01m
YELLOW  = \x1b[33;01m
GREEN   = \x1b[32;01m
RED     = \x1b[31;01m
BLACK   = \x1b[30;01m
RESET   = \x1b[0m

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(YELLOW)/-----	Compiling $(NAME)		-----\\ $(RESET)"
	$(CXX) $(INCLUDES) $(OBJ) $(FLAGS) -o $(NAME)

%.o: %.c
	@$(CXX) $(INCLUDES) $(FLAGS) -c $< -o $@

clean:
	@echo "$(RED)/-----	Cleaning $(NAME)		-----\\ $(RESET)"
	rm -f $(OBJ)
fclean: clean
	@echo "$(BLUE)/-----	Fcleaning $(NAME)		-----\\ $(RESET)"
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re
