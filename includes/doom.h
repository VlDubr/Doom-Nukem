/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmcclure <vmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:40:29 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/19 20:03:59 by vmcclure         ###   ########.fr       */
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
# include "../lib/TGA-Reader/include/tga.h"
# include "filesystem.h"
# include "physics.h"
# include <stdlib.h>
# ifdef __APPLE__
#  define CREATEFLAG S_IWRITE | S_IREAD
#  include "../lib/SDL/include/SDL2/SDL.h"
# elif __linux__
#  define CREATEFLAG __S_IWRITE | __S_IREAD
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

typedef struct	s_bar
{
	t_rgba		color;
	t_fvector2d	pos;
	t_fvector2d	widthheight;
}				t_bar;
t_bar		setbar(t_rgba color, t_fvector2d pos, t_fvector2d wh);
void		drawbar(uint32_t *p, t_bar bar);

typedef struct	s_anim
{
	t_tga		*frame;
	t_tga		thisframe;
	int			maxframe;
	int			countframe;
	int			state;
}				t_anim;
t_anim			setanim(t_tga *frame, int maxframe);
void			startanim(t_anim *anim);
void			stopanim(t_anim *anim);
void			pauseanim(t_anim *anim);
void			unpauseanim(t_anim *anim);
void			nextframe(t_anim *anim);
void			previousframe(t_anim *anim);

typedef struct	s_mouse
{
	t_ivector2d	old;
	t_ivector2d	mousepos;
	float		sensivety;
}				t_mouse;

typedef struct	s_input
{
	t_mouse		mouse;
	const Uint8	*keystate;
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

	size_t		targetid;

	float		height;
	float		maxhealth;
	float		health;
	float		maxstamina;
	float		stamina;

	float		maxheightjump;
	float		movespeed;
	float		runspeed;

	int			run;
	int			jump;
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

typedef struct	s_wall
{
	t_fvector	p[4];
	t_tga		texture;
}				t_wall;

typedef struct	s_doom
{
	char		*path;
	t_window	*win;
	SDL_Event	event;

	Uint64		lastframe;
	Uint64		currentframe;
	double		delta;

	t_input		input;

	t_player	player;

	t_map		*maps;
	size_t		mapcount;
	size_t		level;
	t_map		thismap;
}				t_doom;

t_tga		*tga;

void		drawpoint(uint32_t *p, t_ivector2d size, t_ivector2d cord, t_rgba color);
void		drawline(uint32_t *p, t_fvector start, t_fvector end, t_rgb color);
void		drawsector(uint32_t *p, t_player play, t_fvector *w, size_t count);
void		drow_wall(uint32_t *p, t_wall wall, t_tga image);
void		drawfloor(uint32_t *p, t_wall wa, t_rgb color);
void		drawceil(uint32_t *p, t_wall wa, t_rgb color);

void		destrotwindow(t_doom *doom);

void		updateevent(t_doom *doom);
void		update(t_doom *doom, double delta);
void		draw(t_doom *doom);
void		drawui(t_doom *doom);
void		quitprogram(t_doom *doom);

t_player	defaultplayerdata(void);
void		addstamina(t_player *p, float addvalue);
void		minusstamina(t_player *p, float minusvalue);
void		playermove(t_doom *doom, double delta);
void		playerjump(t_doom *doom, t_player *player);

void		loadinput(char *path, t_input *input);

int			collide(t_fvector2d pos, t_fvector2d newpos,
t_fvector *w, size_t count);
int			inside(t_fvector2d i, t_fvector *p, size_t size);
size_t		isinside(t_fvector2d pos, t_map	map, size_t	lastsecid);

void		loadassets(char *path, t_doom *doom);
t_map		loadmap(char *path);
void		switchlevel(t_doom *doom, size_t level);

void		free2dstring(char **str);
size_t		stringcount(char **str);
void		error(const char *str);

#endif
