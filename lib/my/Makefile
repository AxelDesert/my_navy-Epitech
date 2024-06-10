##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## ee
##

SRC 	=	my_strcmp.c	\
			my_str_to_word_array.c	\
			my_getnbr.c	\
			my_getnbr_char.c\
			my_putstr.c	\
			my_put_nbr.c\
			my_getdigit.c\
			my_strdup.c	\
			my_strlen.c

OBJ	=	$(SRC:.c=.o)

NAME	=	libmy.a

all:	$(NAME)

$(NAME): 	$(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)
	rm -f *.gcno
	rm -f *.gcda
	rm -f *.html

fclean: clean
	rm -f $(NAME)

re: fclean all
