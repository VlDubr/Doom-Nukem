/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inside.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:47:14 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/11 19:27:29 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	inside(t_fvector2d i, t_fvector *p, size_t size)
{
	size_t		c;
	size_t		prev;
	int			b;

	c = 0;
	b = 0;
	prev = size - 1;
	while (c < size)
	{
		if ((((p[c].y <= i.y) && (i.y < p[prev].y)) ||
		 ((p[prev].y <= i.y) && (i.y < p[c].y))) &&
		(i.x < ((p[prev].x - p[c].x) * (i.y - p[c].y) / (p[prev].y - p[c].y) + p[c].x)))
			b++;
		prev = c;
		c++;
	}
	return (b&1) != 0;
}

size_t	isinside(t_fvector2d pos, t_map	map, size_t	lastsecid)
{
	size_t count;

	count = 0;
	if (!inside(pos, map.walls + map.sectors[lastsecid].start,
	map.sectors[lastsecid].count))
	{
		while (count < map.sectorcount)
		{
			if (inside(pos, map.walls + map.sectors[count].start,
			map.sectors[count].count))
				return (count);
			count++;
		}
	}
	return (lastsecid);
}
