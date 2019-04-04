/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:40:29 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/04 18:59:54 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H
# include "../lib/libft/includes/libft.h"
# include "../lib/ft_graphics/includes/vector.h"
# include "../lib/ft_graphics/includes/rotate.h"
# include "../lib/ft_graphics/includes/mat.h"
# include "../lib/ft_graphics/includes/utils.h"
# include "../lib/ft_graphics/includes/color.h"
# include "filesystem.h"
# include <stdlib.h>
# ifdef __APPLE__
#  include "../lib/SDL/include/SDL2/SDL.h"
# elif __linux__
#  include <SDL2/SDL.h>
# endif

typedef struct	s_window
{
	SDL_Window		*window;
	t_ivector2d		size;
	SDL_Surface		*surf;
	SDL_Renderer	*renderer;
	int				state;
}				t_window;
t_window		*createwindow(t_ivector2d size, char *title, Uint32 flag);

typedef struct	s_mouse
{
	t_ivector2d	old;
	t_ivector2d	mousepos;
	float		sensivety;
}				t_mouse;

typedef struct	s_input
{
	t_mouse		mouse;
	int			input[4];
}				t_input;

typedef struct	s_player
{
	t_fvector	pos;
	t_fvector	rotate;
	t_fvector	velosity;

	float		maxhealth;
	float		health;
	float		maxstamina;
	float		stamina;

	float		maxheightjump;
	float		movespeed;
	float		runspeed;

	int			state;
}				t_player;

typedef struct	s_wall
{
	int			sp;
	int			ep;
	int			texture;
	int			nextsector;
}				t_wall;

typedef struct	s_sector
{
	t_wall	*walls;
	size_t	wallcount;
	int		floor;
	int		ceiling;
}				t_sector;

typedef struct	s_map
{
	t_sector	*sectors;
	size_t		sectorcount;
	t_fvector2d	*walls;
	size_t		wallcount;
	t_player	startplayer;
}				t_map;

typedef struct	s_doom
{
	char		*path;
	t_window	*win;
	SDL_Event	event;
	t_input		input;
	t_player	player;
	t_map		thismap;
}				t_doom;

void		drawwall(t_fvector startx, t_fvector endx, t_rgb color);
t_map		testmap(void);

void		destrotwindow(t_doom *doom);

void		updateevent(t_doom *doom);
void		update(t_doom *doom);
void		draw(t_doom *doom);
void		quitprogram(t_doom *doom);

t_player	defaultplayerdata(void);
t_fvector2d	nextplayerposition(t_player player);
void		playermove(t_player *player, t_fvector2d dir);
void		playerjump(t_player *player);

int			deserializeint(char *str, char *name, int *nb);
void		serializeint(int fd, char *name, int nb);

void		loadinput(char *path, t_input *input);

void		free2dstring(char **str);
size_t		stringcount(char **str);
void		error(const char *str);

#endif
