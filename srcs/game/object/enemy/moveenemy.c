/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moveenemy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 14:47:39 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/03 18:23:46 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		initvisit(int *visit, size_t count)
{
	size_t		i;

	i = -1;
	while (++i < count)
		visit[i] = 0;
}

t_fvector2d		checldir(t_line *line, t_object *obj, t_player play,
float delta)
{
	t_fvector2d	dir;
	float		lenv;

	dir = setfvector2d(obj->pos.x - play.pos.x,
	obj->pos.z - play.pos.z);
	lenv = sqrt((dir.x * dir.x) + (dir.y * dir.y));
	dir = divfvector2d(dir, lenv, lenv);
	obj->velosity = setfvector(obj->pos.x - ((dir.x * obj->movespeed) * delta),
	obj->pos.y, obj->pos.z - ((dir.y * obj->movespeed) * delta), 1);
	line->p[0] = setfvector2d(obj->pos.x, obj->pos.z);
	line->p[1] = setfvector2d(obj->velosity.x, obj->velosity.z);
	return (dir);
}

void			moveenemy(t_doom *doom, t_object *obj, float delta)
{
	t_fvector2d	dir;
	t_line		line;
	int			visit[doom->thismap.sectorcount];
	size_t		lastsector;
	t_sector	sec;

	initvisit(visit, doom->thismap.sectorcount);
	dir = checldir(&line, obj, doom->player, delta);
	sec = doom->thismap.sectors[obj->sector];
	if (!(obj->ismoveble && obj->ismove) ||
	collides(line, &doom->thismap, obj->sector, visit))
		return ;
	lastsector = obj->sector;
	obj->sector = isinside(setfvector2d(obj->velosity.x,
	obj->velosity.z), doom->thismap, obj->sector);
	if (lastsector != obj->sector)
	{
		if ((obj->velosity.y / 1.5f) < sec.floor ||
		obj->velosity.y > sec.floor + sec.height)
		{
			obj->sector = lastsector;
			return ;
		}
	}
	obj->pos = obj->velosity;
}
