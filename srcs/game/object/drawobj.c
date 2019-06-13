/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawobj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:14:48 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/13 18:03:01 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	initwallobj(t_map map, t_wall *wa, size_t c)
{
	wa->p[0] = setfvector(map.obj[c].pos.x,
	map.sectors[map.obj[c].sector].floor, map.obj[c].pos.z +
	(map.obj[c].width / 2), 10);
	wa->p[1] = setfvector(map.obj[c].pos.x,
	map.sectors[map.obj[c].sector].floor, map.obj[c].pos.z -
	(map.obj[c].width / 2), 10);
	wa->p[2] = addfvector(wa->p[0], 0, map.obj[c].height, 0);
	wa->p[3] = addfvector(wa->p[1], 0, map.obj[c].height, 0);
	subdrawwall(wa->p, map.obj[c].pos.x, map.obj[c].pos.y, map.obj[c].pos.z);
}

void	objotherdata(t_wall *wal, t_player *play, size_t c, t_map map)
{
	t_wall wa;

	wa = *wal;
	if (wa.p[0].x < 400 && wa.p[0].y > 400 && wa.p[1].x >
	400 && wa.p[1].y > 400 && wa.p[2].x < 400 && wa.p[2].y
	< 400 && wa.p[3].x > 400 && wa.p[3].y < 400)
		play->targetid = c;
	wal->type = 0;
	wal->light = map.sectors[map.obj[c].sector].light;
}

void	objproj(t_wall *wa, t_sermat mat)
{
	wallproj(wa->p, mat.projec);
	if (wa->p[0].x > wa->p[1].x)
	{
		ft_swap((void**)&wa->p[0], (void**)&wa->p[1]);
		ft_swap((void**)&wa->p[2], (void**)&wa->p[3]);
		ft_swap((void**)&wa->offset[1], (void**)&wa->offset[0]);
	}
}

int		drawobjnorm(t_doom *doom, t_wall *wa, t_sermat mat, size_t c)
{
	t_fvector dir;

	dir = subfvtofv(doom->player.pos, doom->thismap.obj[c].pos);
	dir = normfvector(dir);
	initwallobj(doom->thismap, wa, c);
	multmatrixdrawwall(wa->p, matroty(atan2(dir.z, dir.x)));
	adddrawwall(wa->p, doom->thismap.obj[c].pos.x, doom->thismap.obj[c].pos.y,
	doom->thismap.obj[c].pos.z);
	wa->offset[0] = 1;
	wa->offset[1] = 1;
	wa->offset[2] = 1;
	wa->offset[3] = 1;
	wa->texture = doom->texture[doom->thismap.obj[c].texture];
	multmatrixdrawwall(wa->p, mat.cammat);
	return (clip(wa->p, wa->offset));
}

void	drawobj(t_doom *doom, t_map map)
{
	t_wall		wa;
	t_sermat	mat;
	size_t		c;

	mat.cammat = matcam(&doom->player);
	mat.projec = matprojection(initcam(setivector2d(800, 800)));
	c = -1;
	while (++c < map.objcount)
	{
		if (map.obj[c].isactive)
			if (drawobjnorm(doom, &wa, mat, c))
			{
				objproj(&wa, mat);
				objotherdata(&wa, &doom->player, c, doom->thismap);
				addwallinlist(&doom->pipeline, wa);
			}
	}
}
