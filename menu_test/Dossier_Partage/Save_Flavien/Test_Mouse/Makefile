CC =		gcc -I ./include 
CFLAGS =	-Wall -Wextra
LIBSDL =	-lSDL2 -lSDL2_image -lSDL2_ttf
NAME =		jeu
SRC =		./src/game_init.c			\
			./src/draw.c				\
			./src/menu.c				\
			./src/menu_event_mouse.c	\
			./src/menu_init.c			\
			./src/play_solo.c			\
			./src/host_game.c			\
			./src/draw_menu.c			\
			./src/draw_button.c			\
			./src/game_event.c			\
			./src/player.c				\
			./src/bombe.c				\
			./src/main.c				\
			./src/destroy_game.c		\
			./src/destroy_menu.c
OBJ =		$(SRC:.c=.o)
RM =		rm -f *.o
$(NAME):	$(OBJ)
			$(CC) $(OBJ) -o $(NAME) $(CFLAGS) $(LIBSDL)
all:		$(NAME)
clean:		
			$(RM) $(OBJ)
fclean:		clean
			$(RM) $(NAME)
re:			fclean all