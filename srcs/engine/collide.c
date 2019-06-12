/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collide.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 18:40:19 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/12 13:52:40 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_line			setline(t_fvector2d a1, t_fvector2d a2,
t_fvector2d b1, t_fvector2d b2)
{
	t_line l;

	l.p[0] = a1;
	l.p[1] = a2;
	l.p[2] = b1;
	l.p[3] = b2;
	return (l);
}

float			area(t_fvector2d a, t_fvector2d b, t_fvector2d c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int				collideline1(float a, float b, float c, float d)
{
	float tmp;

	if (a > b)
	{
		tmp = a;
		a = b;
		b = tmp;
	}
	if (c > d)
	{
		tmp = c;
		c = d;
		d = tmp;
	}
	return (ft_fmax(a, c) <= ft_fmin(b, d));
}

int				collideline(t_line line)
{
	if (collideline1(line.p[0].x, line.p[1].x, line.p[2].x, line.p[3].x))
		if (collideline1(line.p[0].y, line.p[1].y, line.p[2].y, line.p[3].y))
			if (area(line.p[0], line.p[1], line.p[2]) *
			area(line.p[0], line.p[1], line.p[3]) <= 0)
				if (area(line.p[2], line.p[3], line.p[0]) *
				area(line.p[2], line.p[3], line.p[1]) <= 0)
					return (1);
	return (0);
}

int				collides(t_line line, t_map *map, size_t sector, int *visit)
{
	size_t		c;
	size_t		i;
	size_t		a;

	c = map->sectors[sector].start;
	i = -1;
	visit[sector] = 1;
	while (++i + c < map->sectors[sector].start + map->sectors[sector].count)
	{
		a = map->sectors[sector].start + map->sectors[sector].count;
		line.p[2] = setfvector2d(map->walls[c + i].x, map->walls[c + i].y);
		line.p[3] = setfvector2d(map->walls[c + i + 1 >= a ? c : c + i + 1].x,
		map->walls[c + i + 1 >= a ? c : c + i + 1].y);
		if (map->walls[c + i].z == -1)
		{
			if (collideline(line))
				return (1);
		}
		else if (map->walls[c + i].w == 1 && collideline(line))
			return (1);
		else if (!visit[(int)map->walls[c + i].z]
		&& collides(line, map, (size_t)map->walls[c + i].z, visit))
			return (1);
	}
	return (0);
}

void		collideobjnorm(t_line *line, t_object *obj, t_sector *sec,
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

int			collideobj(t_line line, t_player play, t_map *map)
{
	t_fvector	p1;
	t_fvector	p2;
	t_fvector	dir;
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
