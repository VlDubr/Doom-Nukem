/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcwall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 19:07:30 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/11 13:23:08 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	setwall(t_doom *doom, t_wall *wall, t_sector sec, t_fvector w[2])
{
	wall->p[0] = setfvector(wall->oldpoint[0].x, sec.floor,
	wall->oldpoint[0].y, 1);
	wall->p[1] = setfvector(wall->oldpoint[1].x, sec.floor,
	wall->oldpoint[1].y, 1);
	wall->p[2] = addfvector(wall->p[0], 0, sec.height, 0);
	wall->p[3] = addfvector(wall->p[1], 0, sec.height, 0);
	wall->floorpoint[0] = raycastfloor(setfvector2d(1.047197551,
	1.047197551),
	setfvector2d(doom->player.pos.y + doom->player.height, sec.floor));
	wall->floorpoint[1] = raycastfloor(setfvector2d(-1.047197551,
	1.047197551),
	setfvector2d(doom->player.pos.y + doom->player.height, sec.floor));
	wall->type = 3;
}

void	setotherwalldata(t_doom *doom, t_wall *wall, t_sector sec, t_ivector ci)
{
	wall->offset[0] = 1;
	wall->offset[1] = 1;
	wall->offset[2] = 1;
	wall->offset[3] = 1;
	wall->texture = doom->texture[sec.walltexture];
	wall->c = ci.x + ci.y;
	wall->light = sec.light;
}

int		setwalls(t_doom *doom, t_wall **wall, t_sector sec, t_ivector ci)
{
	t_fvector	w[2];
	t_ivector2d	ij;

	ij.x = 0;
	w[0] = doom->thismap.walls[ci.x + ci.y];
	w[1] = doom->thismap.walls[ci.x + ci.y + 1 >= ci.x + sec.count ?
	sec.start : ci.x + ci.y + 1];
	(*wall)[0].oldpoint[0] = w[0];
	(*wall)[0].oldpoint[1] = w[1];
	(*wall)[1].oldpoint[0] = w[0];
	(*wall)[1].oldpoint[1] = w[1];
	(*wall)[0].floorpoint[0] = setfvector(0, 0, 0, 0);
	(*wall)[0].floorpoint[1] = setfvector(0, 0, 0, 0);
	(*wall)[0].type = 0;
	(*wall)[1].type = 0;
	if (w[0].z == -1)
		setwall(doom, &(*wall)[0], sec, w);
	else
	{
		ij.x = portal(doom, wall, &sec, &doom->thismap.sectors[(int)w[0].z]);
		//if (doom->visit[doom->thismap.sectors[(int)w[0].z].id] == 0)
		//	drawwallv3(doom, w[0].z);
	}
	ij.y = ij.x + 1;
	while (--ij.y > -1)
		setotherwalldata(doom, &(*wall)[ij.y], sec, ci);
	return (ij.x);
}
