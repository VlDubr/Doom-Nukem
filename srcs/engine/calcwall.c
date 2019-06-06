/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcwall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 19:07:30 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/06 19:07:45 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	setwall(t_wall *wall, t_sector sec, t_fvector w[2])
{
	wall->p[0] = setfvector(w[0].x, sec.floor, w[0].y, 1);
	wall->p[1] = setfvector(w[1].x, sec.floor, w[1].y, 1);
	wall->p[2] = addfvector(wall->p[0], 0, sec.height, 0);
	wall->p[3] = addfvector(wall->p[1], 0, sec.height, 0);
}

void	setotherwalldata(t_doom *doom, t_wall *wall, t_sector sec, t_ivector ci)
{
	wall->offset[0] = 1;
	wall->offset[1] = 1;
	wall->offset[2] = 1;
	wall->offset[3] = 1;
	wall->texture = doom->texture[sec.walltexture];
	wall->c = ci.x + ci.y;
}

int		setwalls(t_doom *doom, t_wall **wall, t_sector sec, t_ivector ci)
{
	t_fvector	w[2];
	int			i;
	int			j;

	j = 0;
	w[0] = doom->thismap.walls[ci.x + ci.y];
	w[1] = doom->thismap.walls[ci.x + ci.y + 1 >= ci.x + sec.count ?
	sec.start : ci.x + ci.y + 1];
	(*wall)[0].oldpoint[0] = w[0];
	(*wall)[0].oldpoint[1] = w[1];
	if (w[0].z == -1)
		setwall(&(*wall)[0], sec, w);
	else
		j = portal(doom, wall, &sec, &doom->thismap.sectors[(int)w[0].z]);
	i = j + 1;
	while (--i > -1)
		setotherwalldata(doom, &(*wall)[i], sec, ci);
	return (j);
}