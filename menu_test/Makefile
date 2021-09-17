CC =	gcc -Wall -Wextra -Werror
NAME =	bomberman
SRC =	./src/game.c				\
		./src/misc.c				\
		./src/object_initializer.c	\
		./src/bombs.c				\
		./src/debug.c				\
		./src/server_init.c			\
		./src/client_init.c			\
		./src/collisions.c			\
		./menu/src/destroy_menu.c	\
		./menu/src/draw_menu.c		\
		./menu/src/menu_event_mouse.c	\
		./menu/src/menu_init.c		\
		./menu/src/menu.c			\
		./src/main.c
HED =	./include/game.h
OBJ =	$(SRC:%.c=%.o)
LIBFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lpthread
RM =	rm -f

$(NAME):	$(OBJ)
			$(CC) $(HED) $(OBJ) -o $(NAME) $(LIBFLAGS)
all:	$(NAME)
clean:
		$(RM) $(OBJ)
fclean: clean
		$(RM) $(NAME)
re:		fclean all