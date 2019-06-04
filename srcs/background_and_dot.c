/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_and_dot.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:26:20 by srafe             #+#    #+#             */
/*   Updated: 2019/06/04 18:26:38 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

void		dot_write(t_serv *s, t_sdl *sdl, t_map *map)
{
	int i;
	int x;
	int y;

	i = 0;
	SDL_SetRenderDrawColor(sdl->r, 0, 200, 0, 255);
	while (i < map->wall_count)
	{
		x = map->walls[i].xy[0] + (s->wh_screen[0] / 2) + s->coord_x;
		y = map->walls[i].xy[1] + (s->wh_screen[1] / 2) + s->coord_y;
		SDL_RenderDrawPoint(sdl->r, x + 1, y);
		SDL_RenderDrawPoint(sdl->r, x, y + 1);
		SDL_RenderDrawPoint(sdl->r, x - 1, y);
		SDL_RenderDrawPoint(sdl->r, x, y - 1);
		SDL_RenderDrawPoint(sdl->r, x, y);
		i++;
	}
}

void		background(t_sdl *sdl)
{
	int	y;
	int	x;

	y = 0;
	while (y < 1000)
	{
		x = 0;
		while (x < 1000)
		{
			if (x % 25 == 0 && y % 25 == 0)
				SDL_SetRenderDrawColor(sdl->r, 230, 184, 255, 255);
			else
				SDL_SetRenderDrawColor(sdl->r, 0, 0, 0, 255);
			SDL_RenderDrawPoint(sdl->r, x, y);
			x++;
		}
		y++;
	}
}
