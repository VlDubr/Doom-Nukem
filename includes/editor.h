/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:28:03 by srafe             #+#    #+#             */
/*   Updated: 2019/05/16 16:23:51 by srafe            ###   ########.fr       */
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

# ifdef __APPLE__
#  define CREATEFLAG S_IWRITE | S_IREAD
#  include "../lib/SDL/include/SDL2/SDL.h"
#  include "../lib/SDL/include/SDL2/SDL_image.h"
# elif __linux__
#  define CREATEFLAG __S_IWRITE | __S_IREAD
#  include <SDL2/SDL.h>
#  include <SDL2/SDL_image.h>
#  include <SDL2/SDL_ttf.h>
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

typedef struct		s_service
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
	SDL_Event		e;
}					t_service;

void				line_dda(t_wall start, t_wall finish, t_sdl *sdl, t_service *s);
void				map_parser(t_service *s, char *str, t_map *map);
void				map_writer(t_sdl *sdl, t_service *s, t_map *map);
void				background(t_service *s, t_sdl *sdl);
void				ft_error(const char *str);
int					ft_max(int x, int y);
#endif
