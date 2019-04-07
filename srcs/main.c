/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:40:04 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/04 19:00:13 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		initsdl(Uint32 sdlflag)
{
	if (SDL_Init(sdlflag))
		error("Error: SDL not init...");
}

t_doom			*initdoom(void)
{
	t_doom	*d;

	initsdl(SDL_INIT_EVERYTHING);
	if (!(d = (t_doom*)malloc(sizeof(t_doom))))
		error("Error: Memory is not allocated");
	d->path = SDL_GetBasePath();
	loadinput(d->path, &d->input);
	d->win = createwindow(setivector2d(800, 600), "DOOM", SDL_WINDOW_RESIZABLE);
	return (d);
}

int				main(int agrc, char **argv)
{
	t_doom	*doom;

	doom = initdoom();
	doom->thismap = testmap();
	doom->player = defaultplayerdata();
	doom->player.pos = doom->thismap.startplayer.pos;
	doom->player.rotate = doom->thismap.startplayer.rotate;
	while (doom->win->state)
	{
		updateevent(doom);
		update(doom);
		draw(doom);
	}
	quitprogram(doom);
	return (0);
}
