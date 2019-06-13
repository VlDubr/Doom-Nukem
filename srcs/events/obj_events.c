/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:39:11 by srafe             #+#    #+#             */
/*   Updated: 2019/06/13 17:07:51 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/editor.h"

void	obj_e(t_serv *s, t_map *map)
{
	if (s->e.button.button == 1 && s->obj_edit < map->obj_count)
		s->obj_edit++;
	else if (s->e.button.button == 3 && s->obj_edit > 0)
		s->obj_edit--;
	if (s->obj_edit == map->obj_count)
		s->obj_add = 1;
	else
		s->obj_add = 0;
}

void	obj_type(t_serv *s, t_map *map)
{
	if (s->e.button.button == 1 && map->obj[s->obj_edit].type_obj < 4)
		map->obj[s->obj_edit].type_obj++;
	else if (s->e.button.button == 3 &&
			map->obj[s->obj_edit].type_obj > 0)
		map->obj[s->obj_edit].type_obj--;
}

int		obj_tex(t_serv *s, t_map *map, int tex)
{
	if (s->e.button.button == 1 && tex + 1 < map->tex_count)
		return (tex + 1);
	else if (s->e.button.button == 3 && tex > 0)
		return (tex - 1);
	return (tex);
}
