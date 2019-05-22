/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 12:53:54 by srafe             #+#    #+#             */
/*   Updated: 2019/05/22 13:01:17 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

static void	keydown(t_serv *s, t_sdl sdl, t_map *map)
{
	if (s->e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		s->quit = 1;
	if (s->e.key.keysym.scancode == SDL_SCANCODE_W)
		s->coord_y -= 25;
	if (s->e.key.keysym.scancode == SDL_SCANCODE_S)
		s->coord_y += 25;
	if (s->e.key.keysym.scancode == SDL_SCANCODE_D)
		s->coord_x += 25;
	if (s->e.key.keysym.scancode == SDL_SCANCODE_A)
		s->coord_x -= 25;
	if (s->e.key.keysym.scancode == SDL_SCANCODE_RETURN)
	{
		s->fd = open("map1.map", O_TRUNC | O_RDWR);
		save_map(map, s);
		close(s->fd);
	}
	writer(s, sdl, map);
}

static void	m_button_down(t_serv *s, t_sdl sdl, t_map *map)
{
	SDL_GetMouseState(&s->mouse_xy[0], &s->mouse_xy[1]);
	if (s->mouse_xy[0] > 1000)
	{
		if (s->mouse_xy[1] < 500)
		{
			if (s->e.button.button == 1 && s->sec_edit < map->sec_count)
				s->sec_edit++;
			else if (s->e.button.button == 3 && s->sec_edit > 0)
				s->sec_edit--;
			gui(s, &sdl);
		}
	}
	else
	{
		if (s->e.button.button == 1)
		{
			add_wall_to_map(map, s);
			writer(s, sdl, map);
		}
		if (s->e.button.button == 3 || s->e.button.button == 2)
		{
			delete_wall(map, s);
			writer(s, sdl, map);
		}
	}
}

void		event(t_serv *s, t_sdl sdl, t_map *map)
{
	while (s->quit == 0)
	{
		while (SDL_PollEvent(&s->e))
		{
			if (s->e.type == SDL_QUIT)
				s->quit = 1;
			if (s->e.type == SDLK_ESCAPE)
				s->quit = 1;
			if (s->e.type == SDL_KEYDOWN)
				keydown(s, sdl, map);
			if (s->e.type == SDL_MOUSEBUTTONDOWN)
				m_button_down(s, sdl, map);
		}
	}
}
