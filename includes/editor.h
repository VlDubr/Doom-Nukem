/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:28:03 by srafe             #+#    #+#             */
/*   Updated: 2019/05/22 17:38:08 by srafe            ###   ########.fr       */
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
	int				next_type;
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
	int				roof_h;
	int				r_visibility;
	int				sec_type;
}					t_sector;

typedef struct		s_map
{
	t_player		player;
	t_sector		*sector;
	t_wall			*walls;
	int				sec_count;
	int				wall_count;
}					t_map;

typedef struct		s_serv
{
	int				i;
	int				j;
	int				w_c;
	int				s_c;
	int				quit;
	int				fd;
	int				parse_flag;
	int				coord_x;
	int				coord_y;
	int				mouse_xy[2];
	int				wh_screen[2];
	int				sec_edit;
	SDL_Event		e;
	t_ivector2d		text_wh;
	t_ivector2d		text_c;
	t_tga			**text;
}					t_serv;

void				ft_error(const char *str);
int					ft_max(int x, int y);
int					ft_str_chr_cpy(char *temp, char *str, int i, char *chr);

void				writer(t_serv *s, t_sdl sdl, t_map *map);
void				background(t_sdl *sdl);
void				gui(t_serv *s, t_sdl *sdl, t_map *map);
void				map_writer(t_sdl *sdl, t_serv *s, t_map *map);
void				line_dda(t_wall st, t_wall f, t_sdl *sd, t_serv *s);

void				event(t_serv *s, t_sdl sdl, t_map *map);
int					check_wall(t_serv *s, t_map *map);
void				add_wall_to_map(t_map *map, t_serv *s);
void				delete_wall(t_map *map, t_serv *s);
int					m_align(int coord);
void				sec_e(t_serv *s, t_map *map);
void				floor_e(t_serv *s, t_map *map);
void				roof_e(t_serv *s, t_map *map);
void				r_vis_e(t_serv *s, t_map *map);

void				save_map(t_map *map, t_serv *s);
char				*save_unit(int i, char *delim);
char				*save_w(t_map *map, int i, char *str_old);
char				*save_s(t_map *map, int i, char *str_old);
char				*save_p(t_map *map, int i, char *str_old);


void				map_parser(t_serv *s, char *str, t_map *map);
int					roof_vis(t_map *map, char *temp, int s_c);
#endif
