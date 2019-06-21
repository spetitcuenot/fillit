# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: spetitcu <spetitcu@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/01/07 09:18:52 by bperez       #+#   ##    ##    #+#        #
#    Updated: 2019/06/21 15:06:10 by spetitcu    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = fillit
CC = gcc
FLAGS = -Wall -Wextra -Werror
INC = fillit.h
SRC = fillit.c parse_file.c coord.c algo_base.c
OBJ = $(SRC:c=o)

.PHONY: all libft clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ./libft/
	$(CC) $(FLAGS) -I$(INC) libft/libft.a $(OBJ) -o $(NAME)
	

%.o : %.c $(INC)
	$(CC) $(FLAGS) -I$(INC) -o $@ -c $<

clean:
	@$(MAKE) -C libft/ clean
	@/bin/rm -f *.o

fclean: clean
	@$(MAKE) -C libft/ fclean
	@/bin/rm -f $(NAME)

re: fclean all
