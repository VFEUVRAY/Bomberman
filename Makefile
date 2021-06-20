CC =	gcc -ansi -Wall -Wextra -Werror
NAME =	demo
SRC =	./src/game.c				\
		./src/misc.c				\
		./src/object_initializer.c	\
		./src/main.c
HED =	./include/game.h
OBJ =	$(SRC:%.c=%.o)
RM =	rm -f

$(NAME):	$(OBJ)
			$(CC) `pkg-config --cflags sdl2 SDL2_image` $(HED) $(OBJ) -o $(NAME) `pkg-config --libs sdl2 SDL2_image`
all:	$(NAME)
clean:
		$(RM) $(OBJ)
fclean: clean
		$(RM) $(NAME)
re:		fclean all