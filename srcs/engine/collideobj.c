/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collideobj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 18:03:10 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/13 18:00:25 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			collideobjnorm(t_line *line, t_object *obj, t_sector *sec,
t_player play)
{
	t_fvector	p1;
	t_fvector	p2;
	t_fvector	dir;

	dir = subfvtofv(play.pos, obj->pos);
	dir = normfvector(dir);
	p1 = setfvector(obj->pos.x, sec->floor, obj->pos.z - (obj->width / 2), 1);
	p2 = setfvector(obj->pos.x, sec->floor, obj->pos.z + (obj->width / 2), 1);
	p1 = subfvector(p1, obj->pos.x, obj->pos.y, obj->pos.z);
	p2 = subfvector(p2, obj->pos.x, obj->pos.y, obj->pos.z);
	p1 = multipmatrix(p1, matroty(atan2(dir.z, dir.x)));
	p2 = multipmatrix(p2, matroty(atan2(dir.z, dir.x)));
	line->p[2] = setfvector2d(p1.x, p1.z);
	line->p[3] = setfvector2d(p2.x, p2.z);
	line->p[2] = addfvector2d(line->p[2], obj->pos.x, obj->pos.z);
	line->p[3] = addfvector2d(line->p[3], obj->pos.x, obj->pos.z);
}

int				collideobj(t_line line, t_player play, t_map *map)
{
	size_t		c;

	c = -1;
	while (++c < map->objcount)
	{
		if (map->obj[c].iscollide)
		{
			collideobjnorm(&line, &map->obj[c],
			&map->sectors[map->obj[c].sector], play);
			if (collideline(line))
				return (1);
		}
	}
	return (0);
}
