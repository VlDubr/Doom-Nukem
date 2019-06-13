/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 13:50:08 by srafe             #+#    #+#             */
/*   Updated: 2019/06/13 17:02:03 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/editor.h"

void	pl_write(t_serv *s, t_sdl sdl)
{
	s->pl_c.x -= (s->player->width / 2);
	s->pl_c.y -= (s->player->height / 2);
	img_write(sdl.r, s->player, s->pl_c);
	s->pl_c.x += (s->player->width / 2);
	s->pl_c.y += (s->player->height / 2);
}

void	pl_add(t_serv *s, t_map *map)
{
	if (s->p_flag == 0)
	{
		s->pl_c.x = s->mouse_xy[0] - s->coord_x;
		s->pl_c.y = s->mouse_xy[1] - s->coord_y;
		map->player.coords[0] = s->mouse_xy[0]
			- (s->wh_screen[0] / 2) - s->coord_x;
		map->player.coords[1] = s->mouse_xy[1]
			- (s->wh_screen[1] / 2) - s->coord_y;
		s->p_flag = 1;
		s->p_add = 0;
	}
}
