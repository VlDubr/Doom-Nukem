/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:58:27 by srafe             #+#    #+#             */
/*   Updated: 2019/06/04 18:03:03 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

static void	gui_colors(t_sdl *sdl, int x, int y)
{
	if (y < 60)
		SDL_SetRenderDrawColor(sdl->r, 92, 92, 92, 255);
	else if (y < 120)
		SDL_SetRenderDrawColor(sdl->r, 139, 0, 139, 255);
	else if (y < 180)
		SDL_SetRenderDrawColor(sdl->r, 139, 69, 19, 255);
	else if (y < 240)
		SDL_SetRenderDrawColor(sdl->r, 123, 2, 43, 255);
	else if (y < 300)
		SDL_SetRenderDrawColor(sdl->r, 128, 128, 0, 255);
	else if (y < 360)
		SDL_SetRenderDrawColor(sdl->r, 47, 79, 79, 255);
	else if (y < 420)
		SDL_SetRenderDrawColor(sdl->r, 0, 0, 100, 255);
	else if (y < 480)
		SDL_SetRenderDrawColor(sdl->r, 0, 100, 0, 255);
	else if (y > 800)
		SDL_SetRenderDrawColor(sdl->r, 139, 69, 19, 255);
	else if (y > 700)
		SDL_SetRenderDrawColor(sdl->r, 200, 0, 0, 255);
	else
		SDL_SetRenderDrawColor(sdl->r, 188, 143, 143, 255);
}

void		gui(t_serv *s, t_sdl *sdl, t_map *map)
{
	int		y;
	int		x;

	y = 0;
	while (y < 1000)
	{
		x = 1000;
		while (x < 1400)
		{
			gui_colors(sdl, x, y);
			SDL_RenderDrawPoint(sdl->r, x, y);
			x++;
		}
		y++;
	}
	text_wr(s, sdl, map);
}
