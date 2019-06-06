NAME = libtga.a
HEAD = ./include/
SRCSFOLDER = ./srcs/
SRCS = ft_error.c h_rec.c memory.c record.c tga_reader.c turn_pic.c bitmap.c \
		write.c
FLAG = -Wall -Wextra -Werror

OBJNAME = $(SRCS:.c=.o)
OBJDIR = ./obj/
OBJ = $(addprefix $(OBJDIR),$(OBJNAME))

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

$(OBJDIR)%.o:$(SRCSFOLDER)%.c
	mkdir -p $(OBJDIR)
	gcc -g $(FLAG) -I $(HEAD) -o $@ -c $<

clean:
	rm -rf $(OBJ)
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)
