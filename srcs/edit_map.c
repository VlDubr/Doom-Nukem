/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:26:53 by srafe             #+#    #+#             */
/*   Updated: 2019/05/21 19:43:38 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

t_sector	*zero_sec(t_map *map)
{
	t_sector *sec;
	int i;

	sec = (t_sector *)malloc(sizeof(t_sector) * (map->sec_count + 1));
	i = -1;
	while (++i < map->sec_count)
		sec[i] = map->sector[i];
	map->sec_count++;
	sec[i].floor_h = 0;
	sec[i].roof_h = 0;
	sec[i].sec_type = 0;
	sec[i].w_count = 0;
	if (i == 0)
		sec[i].start_pos = 0;
	else
		sec[i].start_pos = sec[i - 1].start_pos + sec[i - 1].w_count;
	free(map->sector);
	return (sec);
}

int			m_align(int coord)
{
	int	x;

	x = coord % 25;
	if (x >= 13)
		x = 25 - x;
	if ((coord + x) % 25 == 0)
		coord += x;
	else
		coord -= x;
	return (coord);
}

void		add_wall_to_map(t_map *map, t_serv *s)
{
	t_wall		*wl;
	int i;

	wl = (t_wall *)malloc(sizeof(t_wall) * (map->wall_count + 1));
	if (map->sec_count == s->sec_edit)
		map->sector = zero_sec(map);
	map->wall_count++;
	i = -1;
	while (++i < map->sector[s->sec_edit].start_pos + map->sector[s->sec_edit].w_count)
		wl[i] = map->walls[i];
	wl[i].xy[0] = m_align(s->mouse_xy[0]) - (s->wh_screen[0] / 2) - s->coord_x;
	wl[i].xy[1] = m_align(s->mouse_xy[1]) - (s->wh_screen[1] / 2) - s->coord_y;
	wl[i].next_sec = -1;
	wl[i].next_type = 0;
	map->sector[s->sec_edit].w_count++;
	while (++i < map->wall_count)
		wl[i] = map->walls[i];
	free(map->walls);
	map->walls = wl;
}

void        delete_wall(t_map *map, t_serv *s)
{
	int i;
	int j;

	i = 0;
	while (i < map->wall_count)
	{
		if (map->walls[i].xy[0] == (m_align(s->mouse_xy[0]) - (s->wh_screen[0] / 2) - s->coord_x) &&
			map->walls[i].xy[1] == (m_align(s->mouse_xy[1]) - (s->wh_screen[1] / 2) - s->coord_y))
		{
			while(++i < map->wall_count)
				map->walls[i - 1] = map->walls[i];
			i--;
			map->wall_count--;
			j = 0;
			while (j < map->sec_count)
			{
				if (map->sector[j].start_pos == i)
				{
					map->sector[j].start_pos++;
					map->sector[j].w_count--;
				}
				else if (map->sector[j].start_pos <= i && i < (map->sector[j].start_pos + map->sector[j].w_count))
					map->sector[j].w_count--;
				j++;
			}
			break;
		}
		i++;
	}
}