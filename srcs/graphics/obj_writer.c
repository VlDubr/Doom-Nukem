/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_writer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 18:44:56 by srafe             #+#    #+#             */
/*   Updated: 2019/06/12 19:09:03 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/editor.h"

char	*text_ch(t_map *map, int i)
{
	if (map->obj[i].type_obj == 0)
		return ("D");
	else if (map->obj[i].type_obj == 1)
		return ("E");
	else if (map->obj[i].type_obj == 2)
		return ("U");
	else if (map->obj[i].type_obj == 3)
		return ("L");
	else if (map->obj[i].type_obj == 4)
		return ("D");
	else
		return ("0");
}

void	obj_writer(t_serv *s, t_sdl sdl, t_map *map)
{
	int			i;
	t_ivector2d	coord;

	i = 0;
	while (i < map->obj_count)
	{
		coord.x = map->obj[i].pos[0] + (s->wh_screen[0] / 2) + s->coord_x - coord.x;
		coord.y = map->obj[i].pos[1] + (s->wh_screen[1] / 2) + s->coord_y - coord.y;
		bitmap_write(sdl.r, s->text_025, coord, text_ch(map, i));
		i++;
	}
}
