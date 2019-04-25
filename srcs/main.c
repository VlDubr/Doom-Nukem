/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:40:04 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/24 18:26:49 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		initsdl(Uint32 sdlflag)
{
	if (SDL_Init(sdlflag))
		error("Error: SDL not init...");
	if ((Mix_Init(MIX_INIT_MP3)) == -1)
		error("Error: SDL_Mixer not init...");
	if ((Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, AUDIO_S16, 2, 4096)) == -1)
		error("OpenAudio error!");
}

t_doom			*initdoom(char *argv0)
{
	t_doom	*d;

	initsdl(SDL_INIT_EVERYTHING);
	if (!(d = (t_doom*)malloc(sizeof(t_doom))))
		error("Error: Memory is not allocated");
	if (!(d->sounds = (t_sound *)malloc(sizeof(t_sound))))
		error("Error: Memory for sound is not allocated");
	d->path = getpath(argv0);
	loadassets(ft_strjoin(d->path, "assets/assets.cfg"), d);
	d->level = 0;
	loadinput(d->path, &d->input);
	d->win = createwindow(setivector2d(800, 600), "DOOM", SDL_WINDOW_RESIZABLE);
	d->win->texture = SDL_CreateTexture(d->win->renderer,
	SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 800, 600);
	d->win->pixels = (uint32_t*)malloc(sizeof(uint32_t) * (800 * 600));
	return (d);
}

int				main(int agrc, char **argv)
{
	t_doom	*doom;

	doom = initdoom(argv[0]);
	doom->player = defaultplayerdata();
	switchlevel(doom, doom->level);
	doom->currentframe = SDL_GetPerformanceCounter();
	tga = tga_reader(argv[1]);
	while (doom->win->state)
	{
		doom->lastframe = doom->currentframe;
		doom->currentframe = SDL_GetPerformanceCounter();
		doom->delta = (double)((doom->currentframe - doom->lastframe) *
		1000 / (double)SDL_GetPerformanceFrequency());
		// printf("delta: %f\n", doom->delta);
		updateevent(doom);
		update(doom, doom->delta);
		draw(doom);
	}
	quitprogram(doom);
	return (0);
}
