/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:28:03 by srafe             #+#    #+#             */
/*   Updated: 2019/06/12 18:59:29 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

# include "../lib/ft_graphics/includes/color.h"
# include "../lib/ft_graphics/includes/vector.h"
# include "../lib/libft/includes/libft.h"
# include "../lib/TGA-Reader/include/tga.h"

# ifdef __APPLE__
#  define CREATEFLAG S_IWRITE | S_IREAD
#  include "../lib/SDL/include/SDL2/SDL.h"
#  include "../lib/SDL/include/SDL2/SDL_image.h"
# elif __linux__
#  define CREATEFLAG __S_IWRITE | __S_IREAD
#  include <SDL2/SDL.h>
# elif __WIN32__
#  define CREATEFLAG __S_IWRITE | __S_IREAD
#  include <C:\MinGW\msys\1.0\include\SDL2\SDL.h>
#  include <C:\MinGW\msys\1.0\include\SDL2\SDL_image.h>
#  include <C:\MinGW\msys\1.0\include\SDL2\SDL_ttf.h>

# endif

typedef struct		s_sdl
{
	SDL_Surface		*sur;
	SDL_Renderer	*r;
	SDL_Window		*win;
	SDL_Event		e;
}					t_sdl;

typedef struct		s_wall
{
	int				xy[2];
	int				next_sec;
	int				sector;
}					t_wall;

typedef struct		s_player
{
	int				coords[2];
	int				cam[3];
}					t_player;

typedef struct		s_sector
{
	int				start_pos;
	int				w_count;

	int				floor_h;
	int				floor_tex;

	int				roof_h;
	int				roof_tex;
	int				r_visibility;

	int				sec_type;
	int				texture;
}					t_sector;

typedef struct		s_obj
{
	int				type_obj;
	int				type_use;
	int				is_collide;
	float			pos[3];
	float			rot[3];
	int				width;
	int				height;
	int				health;
	int				is_mov;
	float			move_s;
	int				agr_area;
	int				texture_up;
	int				texture_down;
	int				texture_left;
	int				texture_right;
	int				damage;
}					t_obj;

typedef struct		s_map
{
	t_player		player;
	t_sector		*sector;
	t_wall			*walls;
	t_tga			*textures;
	t_obj			*obj;
	int				obj_count;
	int				tex_count;
	int				sec_count;
	int				wall_count;
}					t_map;

typedef struct		s_serv
{
	char			*file;
	char			*prog_path;
	int				i;
	int				j;
	int				w_c;
	int				s_c;
	int				o_c;
	int				quit;
	int				fd;
	int				parse_flag;
	int				coord_x;
	int				coord_y;
	int				mouse_xy[2];
	int				wh_screen[2];
	int				sec_edit;
	int				obj_edit;
	SDL_Event		e;
	t_ivector2d		text_wh;
	t_ivector2d		text_025_wh;
	t_ivector2d		text_c;
	t_tga			**text;
	t_tga			**text_025;
	t_ivector2d		pl_c;
	t_tga			*player;
	int				p_add;
	int				p_flag;
	int				gui_flag;
	int				obj_add;
}					t_serv;

void				ft_error(const char *str);
int					ft_max(int x, int y);
int					ft_str_chr_cpy(char *temp, char *str, int i, char *chr);

void				writer(t_serv *s, t_sdl sdl, t_map *map);
void				background(t_sdl *sdl);
void				gui(t_serv *s, t_sdl *sdl, t_map *map);
void				map_writer(t_sdl *sdl, t_serv *s, t_map *map);
void				pl_write(t_serv *s, t_sdl sdl);
void				line_dda(t_wall st, t_wall f, t_sdl *sd, t_serv *s);
void				buttons(t_serv *s, t_sdl *sdl, t_map *map);
void				obj_buttons(t_serv *s, t_sdl *sdl, t_map *map);
void				dot_write(t_serv *s, t_sdl *sdl, t_map *map);
void				tex_write(t_serv *s, t_sdl sdl, t_map *map);

void				event(t_serv *s, t_sdl sdl, t_map *map);
int					check_wall(t_serv *s, t_map *map);
int					check_double_wall(t_serv *s, t_map *map);
void				add_wall_to_map(t_map *map, t_serv *s);
int					add_port(t_serv *s, t_map *map);
void				delete_wall(t_map *map, t_serv *s);
void				del_sec(t_serv *s, t_map *map);
int					m_align(int coord);
void				sec_e(t_serv *s, t_map *map);
void				sec_tex(t_serv *s, t_map *map);
void				floor_e(t_serv *s, t_map *map);
void				roof_e(t_serv *s, t_map *map);
void				act_pl(t_serv *s, t_map *map);
void				r_vis_e(t_serv *s, t_map *map);
void				pl_add(t_serv *s, t_map *map);
int					check_w_entry(t_sector *s, int count, int comp);
void				wall_sector_wr(t_map *map);
void				pl_coords_init(t_map *map, t_serv *s);
void				fl_texture(t_serv *s, t_map *map);
void				roof_texture(t_serv *s, t_map *map);
void				button_events(t_serv *s, t_map *map);
void				obj_events(t_serv *s, t_map *map);

char				*init(t_map *map, t_serv *s, char **argv);
void				save_map(t_map *map, t_serv *s);
char				*save_unit(int i, char *delim);
char				*save_w(t_map *map, int i, char *str_old);
char				*save_s(t_map *map, int i, char *str_old);
char				*save_p(t_map *map, char *str_old);
char				*save_obj(t_map *map, int i, char *str_old);
void				clr_map(t_map *map, t_serv *s);
char				*save_elem(char *str, int num, char *c);
char				*save_elem_fl(char *str, float num, char *c);
int					roof_c(int i, t_map *map);

void				map_parser(t_serv *s, char *str, t_map *map);
void				img_parse(char *assets, char *images,
						t_map *map, t_serv *s);
char				*file_read(int fd, char *file);
int					roof_vis(t_map *map, char *temp, int s_c);
void				del_str_mass(char **str);
void				drawimage(t_sdl *sdl, int xy[2],
					int wh[2], t_tga *image);
int					wall_p(t_map *map, char *str, int i, int w_c);
int					sec_p(t_map *map, char *str, int i, int s_c);
int					pl_p(t_map *map, char *str, int i);
int					obj_p(t_map *map, char *str, int i, int o_c);

void				str_wr(t_serv *s, t_sdl *sdl, char *str, char *temp2);
char				*ret_str(int flag, t_map *map, int sec_edit);

void				add_obj(t_map *map, t_serv *s);
void				obj_e(t_serv *s, t_map *map);
void				obj_type(t_serv *s, t_map *map);
int					obj_tex(t_serv *s, t_map *map, int tex);
int					obj_num(t_serv *s, t_map *map, int num);
float				obj_fl(t_serv *s, t_map *map, float num);
void				obj_movable(t_serv *s, t_map *map);
void				del_obj(t_map *map, t_serv *s);
void				obj_to_map(t_serv *s, t_map *map);
void				obj_writer(t_serv *s, t_sdl sdl, t_map *map);
#endif
