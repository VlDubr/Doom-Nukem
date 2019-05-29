/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moveenemy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 14:47:39 by gdaniel           #+#    #+#             */
/*   Updated: 2019/05/29 18:58:56 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	moveenemy(t_player play, t_map *map, t_object *obj, float delta)
{
	t_fvector2d	dir;
	float		lenv;
	size_t		lastsector;

	if (obj->ismoveble && obj->ismove)
	{
		dir = setfvector2d(obj->pos.x - play.pos.x, obj->pos.z - play.pos.z);
		lenv = sqrt((dir.x * dir.x) + (dir.y * dir.y));
		dir = divfvector2d(dir, lenv, lenv);
		obj->velosity.x = obj->pos.x - ((dir.x * obj->movespeed) * delta);
		obj->velosity.z = obj->pos.z - ((dir.y * obj->movespeed) * delta);
		if (collide(setfvector2d(obj->pos.x, obj->pos.z),
			setfvector2d(obj->velosity.x, obj->velosity.z),
			map->walls + map->sectors[obj->sector].start,
			map->sectors[obj->sector].count))
			return ;
		lastsector = obj->sector;
		obj->sector = isinside(setfvector2d(obj->velosity.x,
		obj->velosity.z), *map, obj->sector);
		if (lastsector != obj->sector)
		{
			if ((obj->velosity.y / 1.5f) < map->sectors[obj->sector].floor ||
			obj->velosity.y > map->sectors[obj->sector].floor
			+ map->sectors[obj->sector].height)
			{
				obj->sector = lastsector;
				return ;
			}
		}
		obj->pos = obj->velosity;
	}
}
