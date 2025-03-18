##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## ee
##

SRC =	./src/main.c				\
		./src/play_game.c			\
		./src/attack.c				\
		./src/wait.c				\
		./src/sig_handler.c			\
		./src/parsing.c				\
		./src/map_boats.c			\
		./src/connecting_terminals.c	\
		./src/handle_hit_miss.c

OBJ	=	$(SRC:.c=.o)

NAME = my_navy

CFLAGS = -g

all: $(NAME)

$(NAME):	makelib $(OBJ)
	gcc -o $(NAME) $(OBJ) -L ./lib/my -lmy -I ./include

doc:
	doxygen documentation.doxy

makelib:
	make -C ./lib/my/

cleanlib:
	make clean -C ./lib/my

tests_run:
	echo "no tests"

clean: cleanlib
	rm -f $(OBJ)
	rm -f *.gcno
	rm -f *.gcda
	rm -f *.html

fclean: clean
	rm -f $(TARGET)

re: fclean all
