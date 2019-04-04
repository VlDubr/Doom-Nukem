/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:41:37 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/04 21:20:22 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	drawsector(t_window *win, t_player player, t_map map, size_t secid)
{
	t_fvector2d	p1;
	t_fvector2d	p2;
	int			y;

	y = 0;
	SDL_SetRenderDrawColor(win->renderer, 255, 255, 255, 255);
	while (y < map.sectors[secid].wallcount)
	{
		p1 = map.walls[map.sectors[secid].walls[y].sp];
		p2 = map.walls[map.sectors[secid].walls[y].ep];
		p1 = subfvector2d(p1, player.pos.x, player.pos.y);
		p2 = subfvector2d(p2, player.pos.x, player.pos.y);
		p1 = addfvector2d(p1, win->size.x / 2, win->size.y / 2);
		p2 = addfvector2d(p2, win->size.x / 2, win->size.y / 2);
		SDL_RenderDrawLine(win->renderer, p1.x, p1.y, p2.x, p2.y);
		y++;
	}
}

void	draw(t_doom *doom)
{
	size_t count;

	count = 0;
	SDL_RenderClear(doom->win->renderer);
	while (count < doom->thismap.sectorcount)
	{
		drawsector(doom->win, doom->player, doom->thismap, count);
		count++;
	}
	SDL_SetRenderDrawColor(doom->win->renderer, 0, 0, 0, 255);
	SDL_RenderPresent(doom->win->renderer);
}
