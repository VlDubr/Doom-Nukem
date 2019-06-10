/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawobj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:14:48 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/10 17:11:26 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	initoffset(t_wall *wa)
{
	wa->offset[0] = 1;
	wa->offset[1] = 1;
	wa->offset[2] = 1;
	wa->offset[3] = 1;
}

void	initwallobj(t_doom *doom, t_map map, t_wall *wa, size_t c)
{
	wa->p[0] = setfvector(map.obj[c].pos.x,
	map.sectors[map.obj[c].sector].floor, map.obj[c].pos.z -
	(map.obj[c].width / 2), 1);
	wa->p[1] = setfvector(map.obj[c].pos.x,
	map.sectors[map.obj[c].sector].floor, map.obj[c].pos.z +
	(map.obj[c].width / 2), 1);
	wa->p[2] = addfvector(wa->p[0], 0, map.obj[c].height, 0);
	wa->p[3] = addfvector(wa->p[1], 0, map.obj[c].height, 0);
	subdrawwall(wa->p, map.obj[c].pos.x, map.obj[c].pos.y, map.obj[c].pos.z);
}

void	drawobj(t_doom *doom, t_map map)
{
	t_wall		wa;
	t_mat4x4	cammat;
	t_mat4x4	projec;
	t_fvector	dir;
	size_t		c;

	cammat = matcam(&doom->player);
	projec = matprojection(initcam(setivector2d(800, 800)));
	c = -1;
	while (++c < map.objcount)
	{
		if (map.obj[c].isactive)
		{
			dir = subfvtofv(doom->player.pos, map.obj[c].pos);
			dir = normfvector(dir);
			initwallobj(doom, doom->thismap, &wa, c);
			multmatrixdrawwall(wa.p, matroty(atan2(dir.z, dir.x)));
			adddrawwall(wa.p, map.obj[c].pos.x, map.obj[c].pos.y, map.obj[c].pos.z);
			initoffset(&wa);
			wa.texture = doom->texture[map.obj[c].texture];
			multmatrixdrawwall(wa.p, cammat);
			if (clip(&doom->player, wa.p, wa.offset, c))
			{
				wallproj(wa.p, projec);
				if (wa.p[0].x > wa.p[1].x)
				{
					ft_swap((void**)&wa.p[0], (void**)&wa.p[1]);
					ft_swap((void**)&wa.p[2], (void**)&wa.p[3]);
					ft_swap((void**)&wa.offset[1], (void**)&wa.offset[0]);
				}
				if (wa.p[0].x < 400 && wa.p[0].y > 400 && wa.p[1].x >
				400 && wa.p[1].y > 400 && wa.p[2].x < 400 && wa.p[2].y
				< 400 && wa.p[3].x > 400 && wa.p[3].y < 400)
					doom->player.targetid = c;
				wa.type = 0;
				wa.light = map.sectors[map.obj[c].sector].light;
				addwallinlist(&doom->pipeline, wa);
			}
		}
	}
}
