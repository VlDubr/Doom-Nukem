/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_sec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 13:23:46 by srafe             #+#    #+#             */
/*   Updated: 2019/06/10 17:32:58 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/editor.h"

static void	clr_port(t_map *map, t_serv *s)
{
	int	j;

	j = 0;
	while (j < map->wall_count)
	{
		if (map->walls[j].next_sec == s->sec_edit)
			map->walls[j].next_sec = -1;
		if (map->walls[j].next_sec > s->sec_edit)
			map->walls[j].next_sec--;
		if (map->walls[j].sector > s->sec_edit)
			map->walls[j].sector--;
		j++;
	}
}

void		del_sec(t_serv *s, t_map *map)
{
	int i;

	clr_port(map, s);
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
