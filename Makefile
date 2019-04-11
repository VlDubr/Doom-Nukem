NAME = doom
SRCS = main.c \
		updateevent.c update.c draw.c quitprogram.c \
		error.c createwindow.c utils.c \
		game/player/playermove.c game/player/nextplayerposition.c game/player/defaultplayerdata.c \
		game/map/testmap.c \
		engine/collide.c engine/inside.c \
		engine/filesystem/fileexist.c engine/filesystem/readfile.c engine/filesystem/getpath.c \
		engine/serialize/serializeint.c engine/serialize/deserializeint.c \
		engine/input/loadinput.c \
		engine/draw/drawwall.c engine/draw/drawline.c
SRCSFOLDER = ./srcs/
OBJNAME = $(SRCS:.c=.o)
OBJDIR = ./obj/
OBJ = $(addprefix $(OBJDIR),$(OBJNAME))
INCLUDES = ./includes/
FLAG = -Wall -Wextra -Werror
BUILDFOLDER = ./build/

ASSETSFOLDER = assets

LIBFTFOLDER = ./lib/libft/
LIBFTINCLUDES = $(LIBFTFOLDER)
LIBFTLINK = -I $(LIBFTINCLUDES) -L $(LIBFTFOLDER) -lft

GRAPHICSFOLDER = ./lib/ft_graphics/
GRAPHICSINCLUDES = $(GRAPHICSFOLDER)includes/
GRAPHICSLINK = -I $(GRAPHICSINCLUDES) -L $(GRAPHICSFOLDER) -lftgraphics

SDL2LINKMACOS = -I ./lib/SDL/include/SDL2/ -F ./lib/SDL/Frameworks/ -framework SDL2
SDL2LINKLINUX = -lm -lSDL2

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFTFOLDER)
	$(MAKE) -C $(GRAPHICSFOLDER)
	cp -r $(ASSETSFOLDER) $(BUILDFOLDER)
	gcc $(FLAG) $(OBJ) $(SDL2LINKMACOS) $(GRAPHICSLINK) $(LIBFTLINK) -o $(NAME)

debugmacos: $(OBJ)
	$(MAKE) -C $(LIBFTFOLDER)
	$(MAKE) -C $(GRAPHICSFOLDER)
	mkdir $(BUILDFOLDER)
	mkdir $(BUILDFOLDER)config
	cp -r $(ASSETSFOLDER) $(BUILDFOLDER)
	gcc -g $(FLAG) $(OBJ) $(SDL2LINKMACOS) $(GRAPHICSLINK) $(LIBFTLINK) -o $(BUILDFOLDER)$(NAME)

debuglinux: $(OBJ)
	$(MAKE) -C $(LIBFTFOLDER)
	$(MAKE) -C $(GRAPHICSFOLDER)
	mkdir $(BUILDFOLDER)
	mkdir $(BUILDFOLDER)config
	cp -r $(ASSETSFOLDER) $(BUILDFOLDER)
	gcc -g $(FLAG) $(OBJ) $(SDL2LINKLINUX) $(GRAPHICSLINK) $(LIBFTLINK) -o $(BUILDFOLDER)$(NAME)

clean:
	$(MAKE) -C $(LIBFTFOLDER) clean
	$(MAKE) -C $(GRAPHICSFOLDER) clean
	rm -rf $(OBJDIR)
	rm -rf *.o

fclean: clean
	$(MAKE) -C $(LIBFTFOLDER) fclean
	$(MAKE) -C $(GRAPHICSFOLDER) fclean
	rm -rf $(BUILDFOLDER)
	rm -rf $(NAME)

$(OBJDIR)%.o:$(SRCSFOLDER)%.c
	$(MAKE) folder
	gcc -g -I $(INCLUDES) -o $@ -c $<

folder:
	mkdir -p $(OBJDIR)engine/draw
	mkdir -p $(OBJDIR)engine/core
	mkdir -p $(OBJDIR)engine/filesystem
	mkdir -p $(OBJDIR)engine/input
	mkdir -p $(OBJDIR)engine/serialize
	mkdir -p $(OBJDIR)engine/sound
	mkdir -p $(OBJDIR)game/map
	mkdir -p $(OBJDIR)game/player

re:	fclean $(NAME)

re_d_macos: fclean debugmacos

re_d_linux: fclean debuglinux
