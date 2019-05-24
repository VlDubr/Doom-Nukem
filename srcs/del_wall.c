/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 16:20:01 by srafe             #+#    #+#             */
/*   Updated: 2019/05/24 16:10:37 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

void		w_del(t_map *map, int j, int i)
{
	if (map->sector[j].start_pos == i)
		map->sector[j].w_count--;
	else if (map->sector[j].start_pos < i &&
			i <= (map->sector[j].start_pos + map->sector[j].w_count))
		map->sector[j].w_count--;
	else if (j + 1 < map->sec_count)
		w_del(map, j + 1, i);
}

int			check_sec(t_map *map, t_serv *s, int i)
{
	int sec;

	sec = 0;
	while (sec < map->sec_count)
	{
		if (i >= map->sector[sec].start_pos
			&& i < map->sector[sec].start_pos + map->sector[sec].w_count
			&& sec == s->sec_edit)
			return (1);
		sec++;
	}
	return (0);
}

void		delete_wall(t_map *map, t_serv *s)
{
	int i;
	int wall;

	i = -1;
	while (++i < map->wall_count)
	{
		if (map->walls[i].xy[0] == m_align(s->mouse_xy[0])
			- (s->wh_screen[0] / 2) - s->coord_x
			&& map->walls[i].xy[1] == m_align(s->mouse_xy[1])
			- (s->wh_screen[1] / 2) - s->coord_y)
		{
			if (check_sec(map, s, i) == 1)
			{
				wall = i;
				while (++i < map->wall_count)
					map->walls[i - 1] = map->walls[i];
				map->wall_count--;
				w_del(map, s->sec_edit, wall);
				i = s->sec_edit;
				while (++i < map->sec_count)
					map->sector[i].start_pos--;
				break ;
			}
		}
	}
}
