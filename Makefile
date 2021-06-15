CC =	gcc
NAME =	demo
SRC =	./src/game.c	\
		./src/misc.c	\
		./src/main.c
HED =	./include/game.h
OBJ =	$(SRC:%.c=%.o)
RM =	rm -f

$(NAME):	$(OBJ)
			$(CC) `pkg-config --cflags sdl2` $(HED) $(OBJ) -o $(NAME) `pkg-config --libs sdl2`
all:	$(NAME)
clean:
		$(RM) $(OBJ)
fclean: clean
		$(RM) $(NAME)
re:		fclean all