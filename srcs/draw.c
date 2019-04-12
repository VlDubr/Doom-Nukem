/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:41:37 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/11 18:37:05 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	cleartexture(t_window *win)
{
	t_ivector2d cord;

	cord.y = 0;
	while (cord.y < win->size.y)
	{
		cord.x = 0;
		while (cord.x < win->size.x)
		{
			win->pixels[cord.x + (cord.y * win->size.x)] = 0;
			cord.x++;
		}
		cord.y++;
	}
}

void	drawsector(uint32_t *p, t_player play, t_fvector *w, size_t count)
{
	t_fvector	p1;
	t_fvector	p2;
	t_rgb		color;
	size_t		c;

	c = 0;
	while (c < count)
	{
		p1 = setfvector(w[c].x, w[c].y, 0);
		p2 = setfvector(w[c + 1 >= count ? 0 : c + 1].x,
		w[c + 1 >= count ? 0 : c + 1].y, 0);
		p1 = subfvector(p1, play.pos.x, play.pos.z, 0);
		p2 = subfvector(p2, play.pos.x, play.pos.z, 0);
		p1 = addfvector(p1, 400, 300, 0);
		p2 = addfvector(p2, 400, 300, 0);
		if (w[c].z == -1)
			color = setrgb(255, 255, 255);
		else
			color = setrgb(255, 0, 0);
		drawline(p, p1, p2, color);
		c++;
	}
}

void	drawplayer(uint32_t *p, t_player play)
{
	t_fvector	dir;

	dir.x = cos(play.rotate.z) * 5;
	dir.y = sin(play.rotate.z) * 5;
	drawline(p, setfvector(400, 300, 0),
	setfvector(400 + dir.x, 300 + dir.y, 0), setrgb(255, 255, 0));
}

void	draw(t_doom *doom)
{
	SDL_RenderClear(doom->win->renderer);
	cleartexture(doom->win);

	drawsector(doom->win->pixels, doom->player, doom->thismap.walls +
	doom->thismap.sectors[doom->player.sector].start,
	doom->thismap.sectors[doom->player.sector].count);

	drawplayer(doom->win->pixels, doom->player);

	SDL_UpdateTexture(doom->win->texture, NULL, doom->win->pixels,
	doom->win->size.x * sizeof(uint32_t));
	SDL_RenderCopy(doom->win->renderer, doom->win->texture, NULL, NULL);
	SDL_SetRenderDrawColor(doom->win->renderer, 0, 0, 0, 255);
	SDL_RenderPresent(doom->win->renderer);
}
