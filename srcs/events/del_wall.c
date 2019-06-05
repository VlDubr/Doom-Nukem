/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 16:20:01 by srafe             #+#    #+#             */
/*   Updated: 2019/06/05 15:34:19 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/editor.h"

void		w_del(t_map *map, int j, int i)
{
	if (map->sector[j].start_pos == i)
		map->sector[j].w_count--;
	else if (check_w_entry(map->sector, j, i) == 1)
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
		if (check_w_entry(map->sector, sec, i) == 1
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
