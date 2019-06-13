/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_writing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 18:02:40 by srafe             #+#    #+#             */
/*   Updated: 2019/06/13 17:42:27 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/editor.h"

static void	main_textures(t_serv *s, t_sdl sdl, t_map *map)
{
	int xy[2];
	int wh[2];

	xy[0] = 1280;
	xy[1] = 67;
	wh[0] = 45;
	wh[1] = 45;
	drawimage(&sdl, xy, wh,
		&map->textures[map->sector[s->sec_edit].texture]);
	xy[0] = 1325;
	xy[1] = 187;
	drawimage(&sdl, xy, wh,
		&map->textures[map->sector[s->sec_edit].floor_tex]);
	xy[0] = 1325;
	xy[1] = 367;
	drawimage(&sdl, xy, wh,
		&map->textures[map->sector[s->sec_edit].roof_tex]);
}

static void	obj_textures(t_serv *s, t_sdl sdl, t_map *map)
{
	int xy[2];
	int wh[2];

	xy[0] = 1255;
	xy[1] = 247;
	wh[0] = 45;
	wh[1] = 45;
	drawimage(&sdl, xy, wh,
		&map->textures[map->obj[s->obj_edit].texture_up]);
	xy[1] += 60;
	xy[0] += 55;
	drawimage(&sdl, xy, wh,
		&map->textures[map->obj[s->obj_edit].texture_down]);
	xy[1] += 60;
	drawimage(&sdl, xy, wh,
		&map->textures[map->obj[s->obj_edit].texture_left]);
	xy[0] += 30;
	xy[1] += 60;
	drawimage(&sdl, xy, wh,
		&map->textures[map->obj[s->obj_edit].texture_right]);
}

void		tex_write(t_serv *s, t_sdl sdl, t_map *map)
{
	if (s->gui_flag == 0 && s->sec_edit < map->sec_count)
		main_textures(s, sdl, map);
	else if (s->gui_flag == 1 && s->obj_edit < map->obj_count)
		obj_textures(s, sdl, map);
}
