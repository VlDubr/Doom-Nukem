/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 18:18:24 by srafe             #+#    #+#             */
/*   Updated: 2019/06/14 14:31:22 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/editor.h"

void		button_events(t_serv *s, t_map *map)
{
	if (s->mouse_xy[1] < 60)
		sec_e(s, map);
	else if (s->mouse_xy[1] < 120 && s->sec_edit < map->sec_count)
		sec_tex(s, map);
	else if (s->mouse_xy[1] < 180 && s->sec_edit < map->sec_count)
		floor_e(s, map);
	else if (s->mouse_xy[1] < 240)
		fl_texture(s, map);
	else if (s->mouse_xy[1] < 300 && s->sec_edit < map->sec_count)
		roof_e(s, map);
	else if (s->mouse_xy[1] < 360 && s->sec_edit < map->sec_count)
		r_vis_e(s, map);
	else if (s->mouse_xy[1] < 420 && s->sec_edit < map->sec_count)
		roof_texture(s, map);
	else if (s->mouse_xy[1] < 480)
		act_pl(s, map);
	else if (s->mouse_xy[1] < 560)
		s->gui_flag = 1;
	else if (s->mouse_xy[1] > 700)
		clr_map(map, s);
}

static void	obj_e_p3(t_serv *s, t_map *map)
{
	if (s->mouse_xy[1] < 780 && s->obj_edit < map->obj_count)
		map->obj[s->obj_edit].move_s =
			obj_fl(s, map, map->obj[s->obj_edit].move_s);
	else if (s->mouse_xy[1] < 820 && s->obj_edit < map->obj_count)
		map->obj[s->obj_edit].damage =
			obj_num(s, map, map->obj[s->obj_edit].damage);
	else if (s->mouse_xy[1] > 820 && s->obj_add == 0)
		s->gui_flag = 0;
}

static void	obj_e_p2(t_serv *s, t_map *map)
{
	if (s->mouse_xy[1] < 420 && s->obj_edit < map->obj_count)
		map->obj[s->obj_edit].texture_left =
			obj_tex(s, map, map->obj[s->obj_edit].texture_left);
	else if (s->mouse_xy[1] < 480 && s->obj_edit < map->obj_count)
		map->obj[s->obj_edit].texture_right =
			obj_tex(s, map, map->obj[s->obj_edit].texture_right);
	else if (s->mouse_xy[1] < 540 && s->obj_edit < map->obj_count)
		map->obj[s->obj_edit].width =
			obj_num(s, map, map->obj[s->obj_edit].width);
	else if (s->mouse_xy[1] < 600 && s->obj_edit < map->obj_count)
		map->obj[s->obj_edit].height =
			obj_num(s, map, map->obj[s->obj_edit].height);
	else if (s->mouse_xy[1] < 660)
		map->obj[s->obj_edit].agr_area =
			obj_num(s, map, map->obj[s->obj_edit].agr_area);
	else if (s->mouse_xy[1] < 720)
		obj_movable(s, map);
	else
		obj_e_p3(s, map);
}

void		obj_events(t_serv *s, t_map *map)
{
	if (s->mouse_xy[1] < 60)
		obj_e(s, map);
	else if (s->mouse_xy[1] < 120 && s->obj_edit == map->obj_count)
		add_obj(map, s);
	else if (s->mouse_xy[1] < 120 && s->obj_edit != map->obj_count)
		del_obj(map, s);
	else if (map->obj_count != 0 && s->obj_edit < map->obj_count)
	{
		if (s->mouse_xy[1] < 180 && s->obj_edit < map->obj_count)
			rotation_ev(s, map);
		else if (s->mouse_xy[1] < 240 && s->obj_edit < map->obj_count)
			obj_type(s, map);
		else if (s->mouse_xy[1] < 300 && s->obj_edit < map->obj_count)
			map->obj[s->obj_edit].texture_up =
				obj_tex(s, map, map->obj[s->obj_edit].texture_up);
		else if (s->mouse_xy[1] < 360 && s->obj_edit < map->obj_count)
			map->obj[s->obj_edit].texture_down =
				obj_tex(s, map, map->obj[s->obj_edit].texture_down);
		else
			obj_e_p2(s, map);
	}
	else if ((map->obj_count == 0 || s->obj_edit == map->obj_count)
		&& s->mouse_xy[1] > 820)
		s->gui_flag = 0;
}
