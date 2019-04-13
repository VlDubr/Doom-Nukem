/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:40:29 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/11 18:37:55 by gdaniel          ###   ########.fr       */
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
	int			rotup;
	int			rotdown;
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

typedef struct	s_sector
{
	size_t			start;
	size_t			count;
	int				floor;
	int				height;
	int				type;
}				t_sector;

typedef struct	s_map
{
	t_sector	*sectors;
	size_t		sectorcount;
	t_fvector	*walls;
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

	t_map		*maps;
	size_t		mapcount;
	size_t		level;
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
void		drawsector(uint32_t *p, t_player play, t_fvector *w, size_t count);
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

size_t		isinside(t_fvector2d pos, t_map	map, size_t	lastsecid);
int			inside(t_fvector2d i, t_fvector *p, size_t size);

void		loadassets(char *path, t_doom *doom);
t_map		loadmap(char *path);
void		switchlevel(t_doom *doom, size_t level);

void		free2dstring(char **str);
size_t		stringcount(char **str);
void		error(const char *str);

int		collide(t_fvector2d pos, t_fvector2d newpos, t_fvector *w,
size_t count);

#endif
