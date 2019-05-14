/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:28:03 by srafe             #+#    #+#             */
/*   Updated: 2019/05/14 17:19:24 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

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
	SDL_Renderer	*ren;
	SDL_Window		*win;
	SDL_Event		e;
}					t_sdl;

typedef struct	s_wall
{
	int start;
	int point_count;
	int next_sec;
	int text_type;
}				t_wall;

typedef struct	s_player
{
	int	coords[2];
	int	cam[3];
}				t_player;

typedef struct	s_sector
{
	int start_pos;
	int w_count;
	int floor_h;
	int roof_h;
	int sec_type;
}				t_sector;

typedef struct	s_map
{
	t_player	player;
	t_sector	*sector;
	t_wall		*walls;
	int			sec_count;
	int			wall_count;

}				t_map;


void	editor(char *path);
#endif