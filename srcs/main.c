/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:40:04 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/09 15:03:41 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		initsdl(Uint32 sdlflag)
{
	if (SDL_Init(sdlflag))
		error("Error: SDL not init...");
}

t_doom			*initdoom(char *argv0)
{
	t_doom	*d;

	initsdl(SDL_INIT_EVERYTHING);
	if (!(d = (t_doom*)malloc(sizeof(t_doom))))
		error("Error: Memory is not allocated");
	d->path = getpath(argv0);
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
	doom->thismap = loadmap(argv[1]);
	//doom->thismap = testmap();
	doom->player = defaultplayerdata();
	doom->player.sector = doom->thismap.startplayer.sector;
	doom->player.pos = doom->thismap.startplayer.pos;
	doom->player.rotate = doom->thismap.startplayer.rotate;
	doom->zbuffer = NULL;
	while (doom->win->state)
	{
		updateevent(doom);
		update(doom);
		draw(doom);
	}
	quitprogram(doom);
	return (0);
}
