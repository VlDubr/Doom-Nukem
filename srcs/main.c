/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmcclure <vmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:40:04 by gdaniel           #+#    #+#             */
/*   Updated: 2019/05/27 17:53:33 by vmcclure         ###   ########.fr       */
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

	if (!(d = (t_doom*)malloc(sizeof(t_doom))))
		error("Error: Memory is not allocated");
	d->path = getpath(argv0);
	loadassets(ft_strjoin(d->path, "assets/assets.cfg"), d);
	d->level = 0;
	loadinput(d->path, &d->input);
	initsdl(SDL_INIT_EVERYTHING);
	d->win = createwindow(setivector2d(800, 800), "DOOM", SDL_WINDOW_RESIZABLE);
	d->win->texture = SDL_CreateTexture(d->win->renderer,
	SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 800, 800);
	d->win->pixels = (uint32_t*)malloc(sizeof(uint32_t) * (800 * 800));
	return (d);
}

int				main(int agrc, char **argv)
{
	char	*file[3];
	t_doom	*doom;
	doom = initdoom(argv[0]);
	doom->player = defaultplayerdata();
	switchlevel(doom, doom->level);
	doom->thismap.obj[1].isagression = 1;
	doom->currentframe = SDL_GetPerformanceCounter();
	tga = tga_reader(ft_strjoin(doom->path, "640x400.tga"));
	tgafloor = tga_reader(ft_strjoin(doom->path, "pol.tga"));
	tgaenemy = tga_reader(ft_strjoin(doom->path, "monster.tga"));
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
