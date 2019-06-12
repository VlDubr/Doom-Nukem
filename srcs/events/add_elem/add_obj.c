/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 13:55:16 by srafe             #+#    #+#             */
/*   Updated: 2019/06/12 17:48:38 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/editor.h"

void	init_obj(t_obj *obj)
{
	obj->type_obj = 0;
	obj->type_use = 0;
	obj->is_collide = 0;
	obj->pos[0] = 0;
	obj->pos[1] = 0;
	obj->pos[2] = 0;
	obj->rot[0] = 0;
	obj->rot[1] = 0;
	obj->rot[2] = 0;
	obj->width = 0;
	obj->height = 0;
	obj->health = 0;
	obj->is_mov = 0;
	obj->move_s = 0;
	obj->agr_area = 0;
	obj->damage = 0;
	obj->texture_up = 0;
	obj->texture_down = 0;
	obj->texture_left = 0;
	obj->texture_right = 0;
}

void	add_obj(t_map *map, t_serv *s)
{
	t_obj	*obj;
	int		i;

	obj = (t_obj *)malloc(sizeof(t_obj) * (map->obj_count + 1));
	i = -1;
	while (++i < map->obj_count)
		obj[i] = map->obj[i];
	init_obj(&obj[map->obj_count]);
	map->obj_count++;
	if (map->obj_count > 1)
		free(map->obj);
	map->obj = obj;
	s->obj_add = 1;
}

void	obj_to_map(t_serv *s, t_map *map)
{
	if (s->obj_add == 1)
	{
		map->obj[s->obj_edit].pos[0] = s->mouse_xy[0]
			- (s->wh_screen[0] / 2) - s->coord_x;
		map->obj[s->obj_edit].pos[1] = s->mouse_xy[1]
			- (s->wh_screen[1] / 2) - s->coord_y;
		s->obj_add = 0;
	}
}
