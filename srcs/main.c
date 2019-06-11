/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:40:04 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/11 18:36:24 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		initsdl(Uint32 sdlflag)
{
	if (SDL_Init(sdlflag))
		error("Error: SDL not init...");
	if ((Mix_Init(MIX_INIT_MP3)) == -1)
		error("Error: SDL_Mixer not init...");
	if ((Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, AUDIO_S16, 2, 256)) == -1)
		error("OpenAudio error!");
}

t_doom			*initdoom(char *argv0)
{
	t_doom	*d;

	if (!(d = (t_doom*)malloc(sizeof(t_doom))))
		error("Error: Memory is not allocated");
	d->path = getpath(argv0);
	initsdl(SDL_INIT_EVERYTHING);
	loadassets(ft_strjoin(d->path, "assets/assets.cfg"), d);
	d->level = 0;
	loadinput(d->path, &d->setting.input);
	initsettingui(d);
	initsetting(&d->setting);
	d->win = createwindow(setivector2d(800, 800), "DOOM", SDL_WINDOW_RESIZABLE);
	d->win->texture = SDL_CreateTexture(d->win->renderer,
	SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 800, 800);
	d->win->pixels = (uint32_t*)malloc(sizeof(uint32_t) * (800 * 800));
	return (d);
}

void			initmenu(t_doom *doom)
{
	doom->newgame.rect = setirect(setivector2d(doom->win->size.x / 2 - 50,
	doom->win->size.y / 2 - 25), 100, 50);
	doom->newgame.texture = doom->texture[1];
	doom->quit.rect = setirect(setivector2d(doom->win->size.x / 2 - 50,
	doom->win->size.y / 2 - 25 + 75), 100, 50);
	doom->quit.texture = doom->texture[1];

	doom->easy.rect = setirect(setivector2d(doom->win->size.x / 2 - 50,
	doom->win->size.y / 2 - 25), 100, 50);
	doom->easy.texture = doom->texture[1];
	doom->middle.rect = setirect(setivector2d(doom->win->size.x / 2 - 50,
	doom->win->size.y / 2 - 25 + 75), 100, 50);
	doom->middle.texture = doom->texture[1];
	doom->hard.rect = setirect(setivector2d(doom->win->size.x / 2 - 50,
	doom->win->size.y / 2 - 25 + 150), 100, 50);
	doom->hard.texture = doom->texture[1];

	doom->gameoverbutton.rect = setirect(setivector2d(doom->win->size.x / 2 - 50,
	doom->win->size.y / 2 - 25), 100, 50);
	doom->gameoverbutton.texture = doom->texture[1];
}

int				main(int agrc, char **argv)
{
	char	*file[3];
	t_doom	*doom;

	doom = initdoom(argv[0]);
	doom->player = defaultplayerdata(doom);
	switchlevel(doom, doom->level);
	doom->thismap.obj[1].isagression = 1;
	doom->currentframe = SDL_GetPerformanceCounter();
	doom->gamestate = 0;
	initmenu(doom);
	while (doom->win->state)
	{
		if (!doom->mouseactive)
			SDL_WarpMouseInWindow(doom->win->window,
			doom->win->size.x / 2, doom->win->size.y / 2);
		SDL_GetMouseState(&doom->setting.input.old.x,
		&doom->setting.input.old.y);
		doom->lastframe = doom->currentframe;
		doom->currentframe = SDL_GetPerformanceCounter();
		doom->delta = (double)((doom->currentframe - doom->lastframe) *
		1000 / (double)SDL_GetPerformanceFrequency());
		updateevent(doom, doom->delta);
		if (doom->gamestate == 1)
			gamescene(doom);
		else
			menuscene(doom);
	}
	quitprogram(doom);
	return (0);
}
