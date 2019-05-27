/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 13:21:14 by srafe             #+#    #+#             */
/*   Updated: 2019/05/27 15:41:34 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

int	check_wall(t_serv *s, t_map *map)
{
	int i;
	int j;
	int x;
	int y;

	i = 0;
	x = m_align(s->mouse_xy[0]) - (s->wh_screen[0] / 2) - s->coord_x;
	y = m_align(s->mouse_xy[1]) - (s->wh_screen[1] / 2) - s->coord_y;
	while (i < map->wall_count)
	{
		if (map->walls[i].xy[0] == x && map->walls[i].xy[1] == y)
		{
			j = 0;
			while (j < map->sec_count)
			{
				if (check_w_entry(map->sector, j, i) == 1 && j == s->sec_edit)
					return (0);
				j++;
			}
		}
		i++;
	}
	return (1);
}

int	check_double_wall(t_serv *s, t_map *map)
{
	int i;
	int j;
	int x;
	int y;

	x = m_align(s->mouse_xy[0]) - (s->wh_screen[0] / 2) - s->coord_x;
	y = m_align(s->mouse_xy[1]) - (s->wh_screen[1] / 2) - s->coord_y;
	i = 0;
	j = 0;
	while (i < map->wall_count)
	{
		if (map->walls[i].xy[0] == x && map->walls[i].xy[1] == y)
			j++;
		if (j > 1)
			return (0);
		i++;
	}
	return (1);
}
