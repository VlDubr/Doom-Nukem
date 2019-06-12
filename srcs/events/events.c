/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 12:53:54 by srafe             #+#    #+#             */
/*   Updated: 2019/06/12 18:43:22 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/editor.h"

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

static void	actions(t_serv *s, t_map *map)
{
	SDL_GetMouseState(&s->mouse_xy[0], &s->mouse_xy[1]);
	if (s->p_add == 1)
		pl_add(s, map);
	else if (s->obj_add == 1)
		obj_to_map(s, map);
	else if (s->e.button.button == 1 && check_wall(s, map) == 1
		&& check_double_wall(s, map) == 1)
		add_wall_to_map(map, s);
	else if (s->e.button.button == 2)
		add_port(s, map);
	else if (s->e.button.button == 3)
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
		if (s->gui_flag == 0)
		{
			if (s->mouse_xy[1] < 800)
				button_events(s, map);
			else if (s->mouse_xy[1] > 800)
			{
				s->fd = open(s->file, O_TRUNC | O_RDWR);
				save_map(map, s);
				close(s->fd);
			}
		}
		else
			obj_events(s, map);
		gui(s, &sdl, map);
	}
	else
		actions(s, map);
	writer(s, sdl, map);
}

void		event(t_serv *s, t_sdl sdl, t_map *map)
{
	s->quit = 0;
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
