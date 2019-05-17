
NAME = editor
HEAD = ./includes/*.h
INC = /usr/local/include
SRCS = ./srcs/*.c
GRAPH = ./lib/ft_graphics/libftgraphics.a
LIBFT = ./lib/libft/libft.a
INC = /usr/local/include
LIB = /usr/local/lib/
FLAG = -Wall -Wextra -Werror
SDL_H = -I ./lib/SDL/include/SDL2/
SDL_F = -F ./lib/SDL/Frameworks -framework SDL2
WIN_SDL_INCL = -I C:/MinGW/msys/1.0/include
WIN_LIB = -L C:/MinGW/msys/1.0/lib

all: $(NAME)
$(NAME): clean
	gcc  -I $(INC) -g -o $(NAME) $(SRCS) $(GRAPH) $(LIBFT) -L $(LIB) $(SDL_H) $(SDL_F)

linux:
	gcc -I $(INC) -g -o $(NAME) $(SRCS) $(GRAPH) $(LIBFT) -L $(LIB) -lm -lSDL2

win:
	gcc $(FLAG) -I $(INC) $(WIN_SDL_INCL) $(WIN_LIB) -g -o $(NAME) $(SRCS) $(GRAPH) $(LIBFT) -L $(LIB) -lmingw32 -lSDL2main -lSDL2

clean:
	@/bin/rm -f *.o

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
