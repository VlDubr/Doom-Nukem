/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:58:27 by srafe             #+#    #+#             */
/*   Updated: 2019/06/12 18:42:08 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/editor.h"

static void	gui_colors(t_sdl *sdl, int y)
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
	else if (y < 540)
		SDL_SetRenderDrawColor(sdl->r, 0, 50, 50, 255);
	else if (y > 800)
		SDL_SetRenderDrawColor(sdl->r, 139, 69, 19, 255);
	else if (y > 700)
		SDL_SetRenderDrawColor(sdl->r, 200, 0, 0, 255);
	else
		SDL_SetRenderDrawColor(sdl->r, 188, 143, 143, 255);
}

static void	obj_gui_colors(t_sdl *sdl, int y)
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
		SDL_SetRenderDrawColor(sdl->r, 0, 50, 0, 255);
	else if (y < 540)
		SDL_SetRenderDrawColor(sdl->r, 139, 69, 19, 255);
	else if (y < 600)
		SDL_SetRenderDrawColor(sdl->r, 0, 50, 50, 255);
	else if (y < 660)
		SDL_SetRenderDrawColor(sdl->r, 100, 100, 0, 255);
	else if (y < 720)
		SDL_SetRenderDrawColor(sdl->r, 39, 100, 50, 255);
	else if (y < 780)
		SDL_SetRenderDrawColor(sdl->r, 100, 0, 100, 255);
	else if (y < 840)
		SDL_SetRenderDrawColor(sdl->r, 0, 100, 133, 255);
	else if (y > 839)
		SDL_SetRenderDrawColor(sdl->r, 139, 69, 19, 255);
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
		while (x < 1500)
		{
			if (s->gui_flag == 0)
				gui_colors(sdl, y);
			else if (s->gui_flag == 1)
				obj_gui_colors(sdl, y);
			SDL_RenderDrawPoint(sdl->r, x, y);
			x++;
		}
		y++;
	}
	if (s->gui_flag == 0)
		buttons(s, sdl, map);
	else if (s->gui_flag == 1)
		obj_buttons(s, sdl, map);
}
