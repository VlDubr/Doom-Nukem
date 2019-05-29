/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 14:59:05 by srafe             #+#    #+#             */
/*   Updated: 2019/05/29 15:00:07 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

static void	service_init(t_serv *s)
{
	s->w_c = 0;
	s->s_c = 0;
	s->parse_flag = 0;
	s->coord_x = 0;
	s->coord_y = 0;
	s->wh_screen[0] = 1000;
	s->wh_screen[1] = 1000;
	s->sec_edit = 0;
	s->text_wh.x = 28;
	s->text_wh.y = 36;
	s->text = bitmap("assets/img/charmap4.tga", s->text_wh);
	s->player = tga_reader("assets/img/man.tga");
	s->pl_c.x = 0;
	s->pl_c.y = 0;
	s->p_flag = 0;
	s->p_add = 0;
	s->text_c.x = 980;
	s->text_c.y = 10;
}

char		*init(t_map *map, t_serv *s, char *file)
{
	map->sec_count = 0;
	map->wall_count = 0;
	map->player.coords[0] = 0;
	map->player.coords[1] = 0;
	map->player.cam[0] = 0;
	map->player.cam[1] = 0;
	map->player.cam[2] = 0;
	service_init(s);
	return (file_read(s, file));
}
