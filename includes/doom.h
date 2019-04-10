/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:40:29 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/09 17:57:04 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H
# include "../lib/libft/includes/libft.h"
# include "../lib/ft_graphics/includes/vector.h"
# include "../lib/ft_graphics/includes/rect.h"
# include "../lib/ft_graphics/includes/rotate.h"
# include "../lib/ft_graphics/includes/mat.h"
# include "../lib/ft_graphics/includes/utils.h"
# include "../lib/ft_graphics/includes/color.h"
# include "filesystem.h"
# include "physics.h"
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
	SDL_Texture		*texture;
	uint32_t		*pixels;
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

typedef enum	e_key
{
	MOVEF = 0,
	MOVEB,
	MOVEL,
	MOVER
}				t_key;


typedef struct	s_input
{
	t_mouse		mouse;
	int			moveforward;
	int			movebackward;
	int			moveleft;
	int			moveright;
	int			rotleft;
	int			rotright;
	int			jump;
}				t_input;

typedef struct	s_player
{
	t_fvector	pos;
	t_fvector	rotate;
	t_fvector	velosity;
	size_t		sector;

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
	t_fvector	view[4];
	int			texture;
	int			nextsector;
}				t_wall;

typedef struct	s_sector
{
	t_wall	*walls;
	size_t	wallcount;
	int		floor;
	int		height;
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
	t_list		*zbuffer;
	SDL_Event	event;
	t_input		input;
	t_player	player;
	t_map		thismap;
}				t_doom;

typedef struct	s_button
{
	t_irect		rect;
	SDL_Surface	*surf;
	void		(*clickevent)(void);
}				t_button;
t_button	setbutton(t_irect r, SDL_Surface *s, void (*clickevent)(void));
int			clickbutton(t_button button, t_mouse mouse);

void		drawline(uint32_t *p, t_fvector start, t_fvector end, t_rgb color);
void		drawsector(uint32_t *p, t_player play, t_map m, size_t secid);
t_map		testmap(void);

void		destrotwindow(t_doom *doom);

void		updateevent(t_doom *doom);
void		update(t_doom *doom);
void		draw(t_doom *doom);
void		quitprogram(t_doom *doom);

t_player	defaultplayerdata(void);
t_fvector2d	retnewpos(float rotz);
void		movelr(SDL_Keycode key, t_doom *doom);
void		movefb(SDL_Keycode key, t_doom *doom);
void		playermove(t_player *player, t_fvector2d dir);
void		playerjump(t_player *player);

void		loadinput(char *path, t_input *input);

void		free2dstring(char **str);
size_t		stringcount(char **str);
void		error(const char *str);

int			collide(t_fvector2d pos, t_fvector2d newpos,
t_map m, size_t secid);

#endif
