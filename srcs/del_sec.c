/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_sec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 13:23:46 by srafe             #+#    #+#             */
/*   Updated: 2019/05/27 15:41:50 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

void	del_sec(t_serv *s, t_map *map)
{
	int i;

	i = map->sector[s->sec_edit].start_pos;
	while (map->sector[s->sec_edit].w_count > 0)
	{
		s->mouse_xy[0] = map->walls[i].xy[0]
				+ (s->wh_screen[0] / 2) + s->coord_x;
		s->mouse_xy[1] = map->walls[i].xy[1]
				+ (s->wh_screen[1] / 2) + s->coord_y;
		delete_wall(map, s);
	}
	i = s->sec_edit;
	while (i < map->sec_count - 1)
	{
		map->sector[i] = map->sector[i + 1];
		i++;
	}
	map->sec_count--;
}
