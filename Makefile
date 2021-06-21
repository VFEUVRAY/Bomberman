CC =	gcc -ansi -Wall -Wextra -Werror
NAME =	demo
SRC =	./src/game.c				\
		./src/misc.c				\
		./src/object_initializer.c	\
		./src/bombs.c				\
		./src/main.c
HED =	./include/game.h
OBJ =	$(SRC:%.c=%.o)
LIBFLAGS = -lSDL2 -lSDL2_image
RM =	rm -f

$(NAME):	$(OBJ)
			$(CC) $(HED) $(OBJ) -o $(NAME) $(LIBFLAGS)
all:	$(NAME)
clean:
		$(RM) $(OBJ)
fclean: clean
		$(RM) $(NAME)
re:		fclean all