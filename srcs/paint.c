/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 17:28:48 by srafe             #+#    #+#             */
/*   Updated: 2019/06/04 18:26:27 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

int			wall_comparing(t_sector *sector, t_wall *walls, int w_c, int i)
{
	int prev;

	prev = sector[walls[w_c].sector].start_pos;
	if (walls[i].next_sec != -1
	&& ((walls[i].xy[0] == walls[w_c + 1].xy[0]
	&& walls[i].xy[1] == walls[w_c + 1].xy[1])
	||
	(walls[i].xy[0] == walls[prev].xy[0]
	&& walls[i].xy[1] == walls[prev].xy[1])))
		return (1);
	return (0);
}

int			search_sec(t_sector *sector, t_wall *walls, int w_c)
{
	int sec;
	int i;

	sec = walls[w_c].next_sec;
	i = sector[sec].start_pos;
	if (i > w_c)
	{
		while (i < (sector[sec].w_count + sector[sec].start_pos))
		{
			if (wall_comparing(sector, walls, w_c, i) == 1)
				return (1);
			i++;
		}
	}
	return (0);
}

void		color_ch(t_sdl *sdl, t_serv *s, t_map *map)
{
	if (s->s_c == s->sec_edit)
		SDL_SetRenderDrawColor(sdl->r, 255, 255, 255, 255);
	else
		SDL_SetRenderDrawColor(sdl->r, 128, 0, 0, 255);
	if (map->walls[s->w_c].next_sec != -1
		&& search_sec(map->sector, map->walls, s->w_c) == 1)
		SDL_SetRenderDrawColor(sdl->r, 0, 128, 128, 255);
}

void		map_writer(t_sdl *sdl, t_serv *s, t_map *map)
{
	s->s_c = map->sec_count - 1;
	while (s->s_c >= 0)
	{
		s->w_c = map->sector[s->s_c].start_pos;
		while (s->w_c < map->sector[s->s_c].w_count +
						map->sector[s->s_c].start_pos)
		{
			color_ch(sdl, s, map);
			if (s->w_c + 1 >= map->sector[s->s_c].w_count
							+ map->sector[s->s_c].start_pos)
				line_dda(map->walls[s->w_c],
						map->walls[map->sector[s->s_c].start_pos], sdl, s);
			else
				line_dda(map->walls[s->w_c], map->walls[s->w_c + 1], sdl, s);
			s->w_c++;
		}
		s->s_c--;
	}
}
