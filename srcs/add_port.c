/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_port.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:44:38 by srafe             #+#    #+#             */
/*   Updated: 2019/05/29 17:55:42 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

int		check_s(t_serv *s, t_map *map, int i, int j)
{
	int	sec[3];

	sec[0] = 0;
	while (sec[0] < map->sec_count)
	{
		if (check_w_entry(map->sector, sec[0], i) == 1)
		{
			sec[1] = sec[0];
			sec[0]++;
			while (sec[0] < map->sec_count)
			{
				if (check_w_entry(map->sector, sec[0], j) == 1)
				{
					sec[2] = sec[0];
					map->walls[i].next_sec = sec[2];
					map->walls[j - 1].next_sec = sec[1];
					return (1);
				}
				sec[0]++;
			}
		}
		sec[0]++;
	}
	return (0);
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
			break ;
		}
		i++;
	}
}
