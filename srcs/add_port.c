/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_port.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:44:38 by srafe             #+#    #+#             */
/*   Updated: 2019/05/24 17:06:40 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

void	check_s(t_serv *s, t_map *map, int i, int j)
{
	int	sec;
	int	sec1;
	int	sec2;

	sec = 0;
	while (sec < map->sec_count)
	{
		if ((map->sector[sec].start_pos < i &&
			i <= (map->sector[sec].start_pos + map->sector[sec].w_count)))
			sec1 = sec;
		if ((map->sector[sec].start_pos < j &&
			j <= (map->sector[sec].start_pos + map->sector[sec].w_count)))
			sec2 = sec;
		sec++;
	}
	map->walls[i].next_sec = sec2;
	map->walls[j].next_sec = sec1;
}

void	add_port(t_serv *s, t_map *map)
{
	int	i;
	int	j;
	int	xy[2];

	i = 0;
	xy[0] = m_align(s->mouse_xy[0]) - (s->wh_screen[0] / 2) - s->coord_x;
	xy[1] = m_align(s->mouse_xy[1]) - (s->wh_screen[1] / 2) - s->coord_y;
	while (i < map->wall_count)
	{
		if (map->walls[i].xy[0] == xy[0] && map->walls[i].xy[1] == xy[1])
		{
			j = i + 1;
			while (j < map->wall_count)
			{
				if (map->walls[j].xy[0] == xy[0]
					&& map->walls[j].xy[1] == xy[1])
					check_s(s, map, i, j);
				j++;
			}
		}
		i++;
	}
}
