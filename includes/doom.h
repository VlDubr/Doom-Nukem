/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:40:29 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/12 13:33:52 by gdaniel          ###   ########.fr       */
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
#  include "../lib/SDL/include/SDL2/SDL_mixer.h"
# elif __linux__
#  define CREATEFLAG __S_IWRITE | __S_IREAD
#  include <SDL2/SDL.h>
#  include <SDL2/SDL_mixer.h>
# elif __WIN32__
#  define CREATEFLAG __S_IWRITE | __S_IREAD
#  include <C:\MinGW\msys\1.0\include\SDL2\SDL.h>
#  include <C:\MinGW\msys\1.0\include\SDL2\SDL_mixer.h>
# endif
# define SIGN(value) (value / abs(value))

typedef struct	s_line
{
	t_fvector2d		p[4];
}				t_line;

t_line			setline(t_fvector2d a1, t_fvector2d a2,
t_fvector2d b1, t_fvector2d b2);

int				collideline(t_line line);

typedef struct	s_camera
{
	float		near;
	float		far;
	float		fov;
	float		aspectratio;
}				t_camera;

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
	t_tga		**frame;
	t_tga		thisframe;
	int			maxframe;
	int			countframe;
	int			state;
}				t_anim;
t_anim			setanim(t_tga **frame, int maxframe);
void			startanim(t_anim *anim);
void			stopanim(t_anim *anim);
void			pauseanim(t_anim *anim);
void			unpauseanim(t_anim *anim);
void			nextframe(t_anim *anim);
void			previousframe(t_anim *anim);

typedef struct	s_input
{
	const Uint8	*keystate;
	int			use;
	int			moveforward;
	int			movebackward;
	int			moveleft;
	int			moveright;
	int			rotleft;
	int			rotright;
	int			rotup;
	int			rotdown;
	int			jump;
	t_ivector2d	old;
	t_ivector2d	mousepos;
	t_fvector2d deltapos;
	float		sensivety;
	int			mousekey[3];
}				t_input;

typedef enum	e_damagetype
{
	MELLE,
	RANGE
}				t_damagetype;

typedef struct	s_weapon
{
	char			*name;
	t_ivector		imagetype;
	size_t			imageid;
	t_anim			anim;
	t_tga			*texture;
	int				texturecount;
	int				thisframe;
	int				animstate;
	int				maxammo;
	int				thisammo;
	t_damagetype	dt;
	int				damage;
}				t_weapon;

typedef struct	s_player
{
	t_fvector	pos;
	t_fvector	rotate;
	t_fvector	velosity;
	int			damagemult;
	size_t		sector;

	t_weapon	*weapons;
	size_t		weaponcount;
	t_weapon	*thisweapon;

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

typedef enum	e_typeobj
{
	DECORE,
	ENEMY,
	USE,
	LIGHTMOD,
	USEDOOR
}				t_typeobj;

typedef enum	e_typeuse
{
	ADDHEALTH,
	ADDAMMO,
	ADDSTAMIN
}				t_typeuse;

typedef struct	s_object
{
	int			isactive;
	t_typeobj	typeobject;
	t_typeuse	typeuse;
	int			iscollide;
	size_t		sector;

	t_fvector	pos;
	t_fvector	rotate;
	t_fvector	velosity;

	float		width;
	float		height;

	int			isdead;
	int			health;
	float		maxhealth;

	int			ismove;
	int			ismoveble;
	float		movespeed;

	int			dsc;
	int			dscmax;
	int			damage;

	int			isagression;
	int			agressionarea;

	size_t		texture;
	size_t		textureup;
	size_t		texturedown;
	size_t		textureleft;
	size_t		texturerigth;
}				t_object;

typedef struct	s_sector
{
	size_t			id;
	size_t			start;
	size_t			count;
	int				floor;
	int				height;
	int				type;
	size_t			walltexture;
	size_t			floortexture;
	float			light;
}				t_sector;

typedef struct	s_map
{
	t_sector	*sectors;
	size_t		sectorcount;
	t_fvector	*walls;
	size_t		wallcount;

	t_object	*obj;
	size_t		objcount;

	t_player	startplayer;
}				t_map;

typedef struct	s_sound
{
	Mix_Chunk	*jump;
	Mix_Chunk	*run;
	Mix_Chunk	*shot;
}				t_sound;

void		agressionememy(t_player *player, t_object *obj);
void		damageenemy(Mix_Chunk *s, t_player *player,
t_object *obj, double delta);

typedef struct	s_wall
{
	int			type;
	t_fvector	oldpoint[2];
	t_fvector	floorpoint[2];
	t_fvector	p[4];
	float		offset[4];
	size_t		c;
	t_tga		texture;
	float		light;
}				t_wall;

typedef struct	s_sermat
{
	t_mat4x4	cammat;
	t_mat4x4	projec;
}				t_sermat;


typedef struct	s_setting
{
	t_input		input;
	t_ivector2d	resolution;
	float		soundvolume;
	float		musicvolume;
}				t_setting;

typedef struct	s_button
{
	t_tga		texture;
	t_irect		rect;
}				t_button;

typedef struct	s_settingui
{
	t_button	plussound;
	t_button	minussound;
	t_button	plusmusic;
	t_button	minusmusic;
}				t_settingui;

typedef struct	s_doom
{
	int			mouseactive;
	int			gamestate;
	char		*path;
	t_window	*win;
	t_list		*pipeline;
	int			*visit;
	int			*portalvisit;
	SDL_Event	event;

	t_sound		sound;

	t_tga		*logo;
	t_tga		*gameoverlogo;
	t_button	newgame;
	t_tga		*newgametga;
	t_button	quit;
	t_tga		*quittga;
	t_button	easy;
	t_tga		*easytga;
	t_button	middle;
	t_tga		*middletga;
	t_button	hard;
	t_tga		*hardtga;
	t_button	gameoverbutton;

	Uint64		lastframe;
	Uint64		currentframe;
	double		delta;

	t_weapon	*weapons;
	size_t		weaponcount;

	t_setting	setting;
	t_settingui	settingui;

	t_tga		*texture;
	size_t		texturecount;
	t_tga		**font;
	t_tga		*skybox;
	t_tga		*door;

	t_player	player;

	t_map		*maps;
	size_t		mapcount;
	size_t		level;
	t_map		thismap;
}				t_doom;

void		gamescene(t_doom *doom);
void		menuscene(t_doom *doom);

void		moveenemy(t_doom *doom, t_object *obj, float delta);

void		initsettingui(t_doom *doom);
void		initsetting(t_setting *s);
void		mousemove(t_player *play, t_input *input, float delta);

void		drawskubox(t_doom *doom);
void		drawpoint(uint32_t *p, t_ivector2d size, t_ivector2d cord,
t_rgba color);
void		drawrect(t_doom *doom, t_irect rect, t_rgba color);
void		drawline(uint32_t *p, t_fvector start, t_fvector end, t_rgb color);
void		drawsector(uint32_t *p, t_player play, t_fvector *w, size_t count);
void		drow_wall(uint32_t *p, t_wall wall, t_tga image, float *offset);
void		drawfloor(t_doom *doom, t_wall wa, int b);
void		drawcail(t_doom *doom, t_wall wa, int b);
void		drawimage(t_doom *doom, t_irect rect, t_tga *image);

void		drawwallv3(t_doom *doom, size_t sec);

void		portal(t_doom *doom, t_list **wall, t_sector *sec, t_fvector old[3]);
void		setwalls(t_doom *doom, t_list **wall, t_sector sec, t_ivector ci);

void		drawammo(t_doom *doom);
void		drawweapon(t_doom *doom);

void		drawobj(t_doom *doom, t_map map);

void		drawminimap(uint32_t *p, t_doom *doom, size_t sector,
t_ivector2d cord);
void		drawoptionmenu(t_doom *doom);

void		drawsort(t_list *list);
void		addwallinlist(t_list **list, t_wall wa);

void		addmusic(t_setting *s);
void		submusic(t_setting *s);
void		addsound(t_setting *s);
void		subsound(t_setting *s);

void		destrotwindow(t_doom *doom);

void		updateevent(t_doom *doom, float delta);
void		update(t_doom *doom, double delta);
void		updateui(t_doom *doom);
void		draw(t_doom *doom);
void		drawui(t_doom *doom);
void		quitprogram(t_doom *doom);

t_player	defaultplayerdata(t_doom *doom);
void		addstamina(t_player *p, float addvalue);
void		minusstamina(t_player *p, float minusvalue);

void		shot(t_doom *doom, Mix_Chunk *s);
void		objpickup(t_input input, t_player *play, t_object *obj);
void		lightmod(t_object *obj, t_map *map, t_input input);
void		opendoor(t_object *obj, t_input input, t_map *map);

void		addhealth(t_player *p, float addvalue);
void		minushealth(t_player *p, float minusvalue);
void		playerdeath(t_player *p, int *gamestate);

void		playermove(t_doom *doom, double delta);
void		playerjump(t_doom *doom, t_player *player);

void		loadinput(char *path, t_input *input);

int			collide(t_fvector2d pos, t_fvector2d newpos,
t_fvector *w, size_t count);
int			collides(t_line line, t_map *map, size_t sector, int *visit);
int			collideobj(t_line line, t_player play, t_map *map);
int			inside(t_fvector2d i, t_fvector *p, size_t size);
size_t		isinside(t_fvector2d pos, t_map	map, size_t	lastsecid);

void		loadassets(char *path, t_doom *doom);
t_map		loadmap(char *path);
void		loadweapons(char *path, char **tmp,
t_weapon **weapon, size_t *count);
void		switchlevel(t_doom *doom, size_t level);

t_mat4x4	matcam(t_player *player);
t_mat4x4	matprojection(t_camera cam);
t_camera	initcam(t_ivector2d sizewin);

int			clip(t_player *player, t_fvector p[4], float offset[4], size_t c);

void		initdrawwall(t_fvector *view);
void		multmatrixdrawwall(t_fvector *view, t_mat4x4 mat);
void		wallproj(t_fvector *view, t_mat4x4 proj);
void		divdrawwall(t_fvector *view, float x, float y, float z);
void		adddrawwall(t_fvector *view, float x, float y, float z);
void		subdrawwall(t_fvector *view, float x, float y, float z);
void		multdrawwall(t_fvector *view, float x, float y, float z);

t_fvector	raycastfloor(t_fvector2d angle, t_fvector2d yse);

t_list		*getlistindex(t_list *list, size_t index);
void		del(void *data, size_t size);
void		free2dstring(char **str);
size_t		stringcount(char **str);
void		error(const char *str);

#endif
