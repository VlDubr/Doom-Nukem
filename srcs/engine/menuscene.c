/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menuscene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:54:06 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/12 17:55:51 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		drawbuttos(t_doom *doom)
{
	if (doom->gamestate == 0)
	{
		drawimage(doom, doom->newgame.rect, &doom->newgame.texture);
		drawimage(doom, doom->quit.rect, &doom->quit.texture);
	}
	else if (doom->gamestate == 2)
	{
		drawimage(doom, doom->easy.rect, &doom->easy.texture);
		drawimage(doom, doom->middle.rect, &doom->middle.texture);
		drawimage(doom, doom->hard.rect, &doom->hard.texture);
	}
	else if (doom->gamestate == 3)
	{
		drawimage(doom, setirect(setivector2d(doom->win->size.x / 2 - 300,
		doom->win->size.y / 2 - 100 - 250), 600, 200), doom->gameoverlogo);
		drawimage(doom, doom->gameoverbutton.rect,
		&doom->gameoverbutton.texture);
	}
}

void		menudraw(t_doom *doom)
{
	SDL_RenderClear(doom->win->renderer);
	cleartexture(doom->win);
	drawimage(doom, setirect(setivector2d(0, 0), doom->win->size.x,
	doom->win->size.y), doom->skybox);
	if (doom->gamestate != 3)
		drawimage(doom, setirect(setivector2d(doom->win->size.x / 2 - 300,
		doom->win->size.y / 2 - 100 - 250), 600, 200), doom->logo);
	drawbuttos(doom);
	SDL_UpdateTexture(doom->win->texture, NULL, doom->win->pixels,
	doom->win->size.x * sizeof(uint32_t));
	SDL_RenderCopy(doom->win->renderer, doom->win->texture, NULL, NULL);
	SDL_RenderPresent(doom->win->renderer);
}

void		menuscene(t_doom *doom)
{
	doom->mouseactive = 1;
	menuupdate(doom);
	menudraw(doom);
}
