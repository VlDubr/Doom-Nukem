/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_events2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 17:06:05 by srafe             #+#    #+#             */
/*   Updated: 2019/06/13 17:07:57 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/editor.h"

int		obj_num(t_serv *s, t_map *map, int num)
{
	if (s->e.button.button == 1)
		return (num + 1);
	else if (s->e.button.button == 3 && num > 0)
		return (num - 1);
	return (num);
}

float	obj_fl(t_serv *s, t_map *map, float num)
{
	if (s->e.button.button == 1)
		return (num + 0.05);
	else if (s->e.button.button == 3 && num > 0)
		return (num - 0.05);
	return (num);
}

void	obj_movable(t_serv *s, t_map *map)
{
	if (s->e.button.button == 1)
		map->obj[s->obj_edit].is_mov = 1;
	else if (s->e.button.button == 3)
		map->obj[s->obj_edit].is_mov = 0;
}
