NAME	= arcade

NAME_NC = ./lib/lib_arcade_ncurses.so

NAME_SDL = ./lib/lib_arcade_SDL.so

NAME_OPEN = ./lib/lib_arcade_openGL.so

NAME_MENU_GRAPH = ./lib/lib_menu_graph.so

NAME_MENU_GAME	= ./lib/lib_menu_game.so

NAME_SN = ./games/lib_arcade_snake.so

NAME_PAC = ./games/lib_arcade_pacman.so

CC	= g++

RM	= rm -f

SRCS	=	srcs/play_game.cpp \
		srcs/play_game2.cpp \
		srcs/play_menu.cpp \
		srcs/main_def.cpp

LIB_NC = ./lib/ncurses/load_lib.cpp \
	./lib/ncurses/load_lib2.cpp

LIB_SDL = ./lib/sdl/load_lib.cpp \
	  ./lib/sdl/load_lib2.cpp

LIB_OPEN = ./lib/openGL/load_lib.cpp \
		./lib/openGL/load_lib2.cpp

LIB_MENU_GRAPH = ./lib/openGL/lib_menu_graph.cpp

LIB_MENU_GAME	= ./lib/openGL/lib_menu_game.cpp

LIB_SN = ./games/snake/snake.cpp

LIB_PAC = ./games/pacman/pacman.cpp

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -I./include
CPPFLAGS += -W -Wall -Wextra -std=c++11 

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) -fPIC -shared -lncurses -ltinfo $(LIB_NC) -o $(NAME_NC) -I./include
	 $(CC) -fPIC -shared $(LIB_SDL) -o $(NAME_SDL) -I./include
	 $(CC) -fPIC -shared $(LIB_OPEN) -o $(NAME_OPEN) -I./include
	 $(CC) -fPIC -shared $(LIB_MENU_GAME) -o $(NAME_MENU_GAME) -I./include
	$(CC) -fPIC -shared $(LIB_MENU_GRAPH) -o $(NAME_MENU_GRAPH) -I./include
	 $(CC) -fPIC -std=c++11 -shared $(LIB_SN) -o $(NAME_SN) -I./include
	$(CC) -fPIC -std=c++11 -shared $(LIB_PAC) -o $(NAME_PAC) -I./include
	 $(CC) $(OBJS) -o $(NAME) -std=c++11 -Wl,--no-as-needed -ldl -lSDL -lGL -lGLU -lglut -lncurses -ltinfo $(LAP)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME) $(NAME_SDL) $(NAME_NC) $(NAME_SN) $(NAME_PAC)

re: fclean all

.PHONY: all clean fclean re
