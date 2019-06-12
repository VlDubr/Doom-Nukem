
NAME = editor
HEAD = ./includes/*.h
INC = /usr/local/include
SRCS = ./srcs/gui/buttons.c ./srcs/gui/gui.c ./srcs/gui/textures.c ./srcs/events/add_elem/add_port.c ./srcs/events/add_elem/add_wall.c \
./srcs/gui/obj_buttons.c ./srcs/events/delete/clr_map.c ./srcs/events/delete/del_sec.c ./srcs/events/delete/del_wall.c ./srcs/events/events.c \
./srcs/events/m_events.c ./srcs/events/add_elem/player.c ./srcs/events/save/save_map_units.c ./srcs/events/save/save_map.c\
./srcs/parser/map_parser.c ./srcs/parser/img_parser.c ./srcs/parser/parser2.c ./srcs/graphics/background_and_dot.c \
./srcs/graphics/paint.c ./srcs/graphics/line_writing.c ./srcs/service/check_walls.c ./srcs/service/init.c ./srcs/service/service_f.c\
./srcs/service/del_str_mass.c ./srcs/graphics/draw_image.c ./srcs/parser/unit_p.c ./srcs/events/save/save_units.c ./srcs/events/obj_events.c \
./srcs/graphics/writer.c ./srcs/graphics/texture_writing.c ./srcs/events/add_elem/add_obj.c ./srcs/events/delete/del_obj.c ./srcs/events/button_events.c \
./srcs/graphics/obj_writer.c ./srcs/main.c
TGA = ./lib/TGA-Reader/libtga.a
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
	gcc -I $(INC) -g -o $(NAME) $(SRCS) $(GRAPH) $(TGA) $(LIBFT) -L $(LIB) $(SDL_H) $(SDL_F)

linux:
	gcc $(FLAG) -I $(INC) -g -o $(NAME) $(SRCS) $(GRAPH) $(TGA) $(LIBFT) -L $(LIB) -lm -lSDL2

win:
	gcc $(FLAG) -I $(INC) $(WIN_SDL_INCL) $(WIN_LIB) -g -o $(NAME) $(SRCS) $(GRAPH) $(TGA) $(LIBFT) -L $(LIB) -lmingw32 -lSDL2main -lSDL2

clean:
	@/bin/rm -f *.o

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
