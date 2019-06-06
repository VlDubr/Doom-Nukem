/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playermove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:38:21 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/04 17:21:16 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		initvisit(int *visit, size_t count)
{
	size_t		i;

	i = -1;
	while (++i < count)
		visit[i] = 0;
}

static void	checkpos(t_doom *doom, t_fvector newvec, t_fvector2d dir)
{
	t_line		line;
	int			visit[doom->thismap.sectorcount];
	size_t		lastsector;
	t_sector	sec;

	initvisit(visit, doom->thismap.sectorcount);
	sec = doom->thismap.sectors[doom->player.sector];
	doom->player.velosity = newvec;
	line.p[0] = setfvector2d(doom->player.pos.x, doom->player.pos.z);
	line.p[1] = setfvector2d(doom->player.velosity.x, doom->player.velosity.z);
	if (collides(line, &doom->thismap, doom->player.sector, visit))
		return ;
	lastsector = doom->player.sector;
	doom->player.sector = isinside(setfvector2d(doom->player.velosity.x,
	doom->player.velosity.z), doom->thismap, doom->player.sector);
	if (lastsector != doom->player.sector)
	{
		if ((doom->player.velosity.y / 1.5f)
		< sec.floor || doom->player.velosity.y > sec.floor + sec.height)
		{
			doom->player.sector = lastsector;
			return ;
		}
	}
	doom->player.pos = doom->player.velosity;
}

t_fvector2d	retdir(t_doom *doom)
{
	t_fvector2d	dir;

	dir = setfvector2d(0, 0);
	if (doom->setting.input.keystate[doom->setting.input.moveforward])
		dir = addfvector2d(dir, cos(doom->player.rotate.z),
		sin(doom->player.rotate.z));
	if (doom->setting.input.keystate[doom->setting.input.movebackward])
		dir = addfvector2d(dir, -cos(doom->player.rotate.z),
		-sin(doom->player.rotate.z));
	if (doom->setting.input.keystate[doom->setting.input.moveright])
		dir = addfvector2d(dir, cos(doom->player.rotate.z + 1.57f),
		sin(doom->player.rotate.z + 1.57f));
	if (doom->setting.input.keystate[doom->setting.input.moveleft])
		dir = addfvector2d(dir, -cos(doom->player.rotate.z + 1.57f),
		-sin(doom->player.rotate.z + 1.57f));
	return (dir);
}

void		playermove(t_doom *doom, double delta)
{
	t_fvector2d	dir;
	t_fvector	newvec;

	dir = retdir(doom);
	if (doom->player.run && doom->player.stamina > 0)
	{
		dir = multfvector2d(dir, doom->player.runspeed
		* delta, doom->player.runspeed * delta);
		minusstamina(&doom->player, 1);
	}
	else
		dir = multfvector2d(dir, doom->player.movespeed * delta,
		doom->player.movespeed * delta);
	newvec = addfvector(doom->player.pos, dir.x, 0, dir.y);
	checkpos(doom, newvec, dir);
}
