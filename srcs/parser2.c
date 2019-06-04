/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 16:29:47 by srafe             #+#    #+#             */
/*   Updated: 2019/05/31 16:29:56 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

void		wall_sector_wr(t_serv *s, t_map *map)
{
	int	c;
	int i;
	int	j;

	c = 0;
	while (c < map->sec_count)
	{
		i = map->sector[c].start_pos;
		j = map->sector[c].w_count + i;
		while (i < j)
		{
			map->walls[i].sector = c;
			i++;
		}
		c++;
	}
}

void		pl_coords_init(t_map *map, t_serv *s)
{
	if (map->player.coords[0] != 0 || map->player.coords[1] != 0)
	{
		s->p_flag = 1;
		s->pl_c.x = map->player.coords[0] + (s->wh_screen[0] / 2);
		s->pl_c.y = map->player.coords[1] + (s->wh_screen[1] / 2);
	}
}