/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 12:53:54 by srafe             #+#    #+#             */
/*   Updated: 2019/05/24 17:03:51 by srafe            ###   ########.fr       */
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
	writer(s, sdl, map);
}

static void	actions(t_serv *s, t_sdl sdl, t_map *map)
{
	if (s->e.button.button == 1 && check_wall(s, map) == 1
		&& check_double_wall(s, map) == 1)
		add_wall_to_map(map, s);
	if (s->e.button.button == 2)
	{
		SDL_GetMouseState(&s->mouse_xy[0], &s->mouse_xy[1]);
		add_port(s, map);
	}
	if (s->e.button.button == 3)
	{
		if (map->sector[s->sec_edit].w_count == 3)
			del_sec(s, map);
		else
			delete_wall(map, s);
	}
}

static void	m_button_down(t_serv *s, t_sdl sdl, t_map *map)
{
	SDL_GetMouseState(&s->mouse_xy[0], &s->mouse_xy[1]);
	if (s->mouse_xy[0] > 1000)
	{
		if (s->mouse_xy[1] < 60)
			sec_e(s, map);
		else if (s->mouse_xy[1] < 120 && s->sec_edit < map->sec_count)
			floor_e(s, map);
		else if (s->mouse_xy[1] < 180 && s->sec_edit < map->sec_count)
			roof_e(s, map);
		else if (s->mouse_xy[1] < 240 && s->sec_edit < map->sec_count)
			r_vis_e(s, map);
		else if (s->mouse_xy[1] > 800)
		{
			s->fd = open(s->file, O_TRUNC | O_RDWR);
			save_map(map, s);
			close(s->fd);
		}
		gui(s, &sdl, map);
	}
	else
		actions(s, sdl, map);
	writer(s, sdl, map);
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
