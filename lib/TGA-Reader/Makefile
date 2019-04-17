
NAME = tga
HEAD = ./include/*.h
INC = /usr/local/include
SRCS = ./srcs/h_rec.c ./srcs/memory.c ./srcs/record.c ./srcs/tga_reader.c
GRAPH = ./ft_graphics/libftgraphics.a
LIBFT = ./Libft/libft.a
INC = /usr/local/include
LIB = /usr/local/lib/
SDL_H = -I ./SDL/include/SDL2/
SDL_F = -F ./SDL/Frameworks/ -framework SDL2
SDL_IMG = -F ./SDL/Frameworks/ -framework SDL2_image
WIN_SDL_INCL = -I C:/MinGW/msys/1.0/include
WIN_LIB = -L C:/MinGW/msys/1.0/lib

all: $(NAME)

$(NAME): clean
	@cc -I $(INC) -g -o $(NAME) $(SRCS) $(GRAPH) $(LIBFT) -L $(LIB) $(SDL_H) $(SDL_F) $(SDL_IMG)

linux:
	@cc -I $(INC) -g -o $(NAME) $(SRCS) $(GRAPH) $(LIBFT) -L $(LIB) -lm -lSDL2 -lSDL2_image

win:
	gcc -I $(INC) $(WIN_SDL_INCL) $(WIN_LIB) -g -o $(NAME) $(SRCS) $(GRAPH) $(LIBFT) -L $(LIB) -lmingw32 -lSDL2main -lSDL2

clean:
	@/bin/rm -f *.o

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
