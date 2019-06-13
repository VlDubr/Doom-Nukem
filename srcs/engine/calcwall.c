/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcwall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 19:07:30 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/13 18:00:05 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	setwall(t_doom *doom, t_list **wall, t_sector sec, t_fvector w[2])
{
	t_wall *wa;

	if ((wa = (t_wall*)malloc(sizeof(t_wall))) == NULL)
		error("Error: mamore not allocated");
	wa->p[0] = setfvector(w[0].x, sec.floor, w[0].y, 1);
	wa->p[1] = setfvector(w[1].x, sec.floor, w[1].y, 1);
	wa->p[2] = addfvector(wa->p[0], 0, sec.height, 0);
	wa->p[3] = addfvector(wa->p[1], 0, sec.height, 0);
	wa->floorpoint[0] = raycastfloor(setfvector2d(1.047197551,
	1.047197551),
	setfvector2d(doom->player.pos.y + doom->player.height, sec.floor));
	wa->floorpoint[1] = raycastfloor(setfvector2d(-1.047197551,
	1.047197551),
	setfvector2d(doom->player.pos.y + doom->player.height, sec.floor));
	wa->type = 3;
	addwallinlist(wall, *wa);
	free(wa);
}

void	setotherwalldata(t_doom *doom, t_wall *wall, t_sector sec, t_ivector ci)
{
	wall->offset[0] = 1;
	wall->offset[1] = 1;
	wall->offset[2] = 1;
	wall->offset[3] = 1;
	wall->texture = wall->type != 6 ?
	doom->texture[sec.walltexture] : *doom->door;
	wall->c = ci.x + ci.y;
	wall->light = sec.light;
}

void	setwalls(t_doom *doom, t_list **wall, t_sector sec, t_ivector ci)
{
	t_fvector	w[3];
	t_list		*tmp;
	t_wall		*wa;

	w[0] = doom->thismap.walls[ci.x + ci.y];
	w[1] = doom->thismap.walls[ci.x + ci.y + 1 >= ci.x + (int)sec.count ?
	sec.start : ci.x + ci.y + 1];
	if (w[0].z == -1)
		setwall(doom, wall, sec, w);
	else
	{
		portal(doom, wall, &sec, w);
		if (doom->visit[doom->thismap.sectors[(int)w[0].z].id] == 0)
			drawwallv3(doom, w[0].z);
	}
	tmp = *wall;
	while (tmp != NULL)
	{
		wa = (t_wall*)tmp->content;
		setotherwalldata(doom, wa, sec, ci);
		tmp->content = wa;
		tmp = tmp->next;
	}
}
