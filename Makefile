NAME = doom
SRCS = main.c \
		updateevent.c update.c draw.c quitprogram.c \
		error.c createwindow.c utils.c \
		game/object/enemy/moveenemy.c game/object/enemy/agression.c game/object/enemy/damageenemy.c game/object/drawobj.c game/object/pickup.c game/object/lightmod.c \
		game/map/switchlevel.c game/map/minimap.c \
		game/player/playermove.c game/player/playerjump.c game/player/health.c game/player/stamina.c game/player/defaultplayerdata.c game/player/shot.c \
		game/ui/bar.c game/ui/drawui.c game/ui/optionmenu.c game/ui/updateui.c game/ui/initsettingui.c \
		engine/collide.c engine/inside.c engine/sort.c engine/addwallinlist.c engine/calcwall.c \
		engine/utils/mat.c engine/utils/wallproj.c engine/utils/wallutils.c engine/utils/stringcount.c engine/utils/getlistindex.c engine/utils/raycastfloor.c engine/utils/del.c \
		engine/setting/initsetting.c engine/setting/sound.c engine/setting/music.c \
		engine/filesystem/fileexist.c engine/filesystem/readfile.c engine/filesystem/getpath.c \
		engine/filesystem/loadassets.c engine/filesystem/loadmap.c engine/filesystem/loadweapon.c \
		engine/serialize/serializeint.c engine/serialize/deserializeint.c \
		engine/input/loadinput.c engine/input/mousemove.c \
		engine/draw/drawwall.c engine/draw/drawline.c engine/draw/drawceil.c engine/draw/drawfloor.c engine/draw/drawpoint.c engine/draw/drawrect.c \
		engine/draw/drawimage.c engine/draw/drawpistol.c engine/draw/anim.c engine/draw/drawammo.c engine/draw/drawportal.c engine/draw/drawskybox.c
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

TGAREADERFOLDER = ./lib/TGA-Reader/
TGAREADERINCLUDES = $(TGAREADERFOLDER)includes/
TGAREADERLINK = -I $(TGAREADERINCLUDES) -L $(TGAREADERFOLDER) -ltga

SDL2LINKMACOS = -I ./lib/SDL/include/SDL2/ -F ./lib/SDL/Frameworks/ -framework SDL2 -framework SDL2_mixer 
SDL2LINKLINUX = -lm -lSDL2

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFTFOLDER)
	$(MAKE) -C $(GRAPHICSFOLDER)
	$(MAKE) -C $(TGAREADERFOLDER)
	cp -r $(ASSETSFOLDER) $(BUILDFOLDER)
	gcc $(FLAG) $(OBJ) $(SDL2LINKMACOS) $(GRAPHICSLINK) $(LIBFTLINK) $(TGAREADERLINK) -o $(NAME)

debugmacos: $(OBJ)
	$(MAKE) -C $(LIBFTFOLDER)
	$(MAKE) -C $(GRAPHICSFOLDER)
	$(MAKE) -C $(TGAREADERFOLDER)
	@mkdir $(BUILDFOLDER)
	@mkdir $(BUILDFOLDER)config
	cp -r $(ASSETSFOLDER) $(BUILDFOLDER)
	gcc -g $(FLAG) $(OBJ) $(SDL2LINKMACOS) $(GRAPHICSLINK) $(LIBFTLINK) $(TGAREADERLINK) -o $(BUILDFOLDER)$(NAME)

debuglinux: $(OBJ)
	$(MAKE) -C $(LIBFTFOLDER)
	$(MAKE) -C $(GRAPHICSFOLDER)
	$(MAKE) -C $(TGAREADERFOLDER)
	@mkdir $(BUILDFOLDER)
	@mkdir $(BUILDFOLDER)config
	cp -r $(ASSETSFOLDER) $(BUILDFOLDER)
	gcc -g $(FLAG) $(OBJ) $(SDL2LINKLINUX) $(GRAPHICSLINK) $(LIBFTLINK) $(TGAREADERLINK) -o $(BUILDFOLDER)$(NAME)

clean:
	$(MAKE) -C $(LIBFTFOLDER) clean
	$(MAKE) -C $(GRAPHICSFOLDER) clean
	$(MAKE) -C $(TGAREADERFOLDER) clean
	rm -rf $(OBJDIR)
	rm -rf *.o

fclean: clean
	$(MAKE) -C $(LIBFTFOLDER) fclean
	$(MAKE) -C $(GRAPHICSFOLDER) fclean
	$(MAKE) -C $(TGAREADERFOLDER) fclean
	rm -rf $(BUILDFOLDER)
	rm -rf $(NAME)

$(OBJDIR)%.o:$(SRCSFOLDER)%.c
	$(MAKE) folder
	gcc -g -I $(INCLUDES) -o $@ -c $<

folder:
	@mkdir -p $(OBJDIR)engine/utils/
	@mkdir -p $(OBJDIR)engine/setting/
	@mkdir -p $(OBJDIR)engine/draw
	@mkdir -p $(OBJDIR)engine/core
	@mkdir -p $(OBJDIR)engine/filesystem
	@mkdir -p $(OBJDIR)engine/input
	@mkdir -p $(OBJDIR)engine/serialize
	@mkdir -p $(OBJDIR)engine/sound
	@mkdir -p $(OBJDIR)game/map
	@mkdir -p $(OBJDIR)game/object/decore
	@mkdir -p $(OBJDIR)game/object/enemy
	@mkdir -p $(OBJDIR)game/player
	@mkdir -p $(OBJDIR)game/ui

re:	fclean $(NAME)

re_d_macos: fclean debugmacos

re_d_linux: fclean debuglinux
