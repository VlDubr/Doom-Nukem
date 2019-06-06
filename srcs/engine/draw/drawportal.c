/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawportal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 19:06:08 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/06 19:06:44 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	setwalldown(t_wall *wall, t_sector *sec, t_sector *newsec)
{
	wall->p[0] = setfvector(wall->oldpoint[0].x, sec->floor,
	wall->oldpoint[0].y, 1);
	wall->p[1] = setfvector(wall->oldpoint[1].x, sec->floor,
	wall->oldpoint[1].y, 1);
	wall->p[2] = addfvector(wall->p[0], 0, newsec->floor, 0);
	wall->p[3] = addfvector(wall->p[1], 0, newsec->floor, 0);
}

int		portal(t_doom *doom, t_wall **wall, t_sector *sec, t_sector *newsec)
{
	int i;

	i = 0;
	if (sec->floor < newsec->floor)
	{
		setwalldown(&(*wall)[0], sec, newsec);
		i++;
	}
	if (sec->height > newsec->height)
	{
		(*wall)[1].p[0] = setfvector((*wall)[0].oldpoint[0].x, newsec->height,
		(*wall)[0].oldpoint[0].y, 1);
		(*wall)[1].p[1] = setfvector((*wall)[0].oldpoint[1].x, newsec->height,
		(*wall)[0].oldpoint[1].y, 1);
		(*wall)[1].p[2] = addfvector((*wall)[1].p[0], 0,
		(sec->floor + sec->height) - newsec->height, 0);
		(*wall)[1].p[3] = addfvector((*wall)[1].p[1], 0,
		(sec->floor + sec->height) - newsec->height, 0);
		i++;
	}
	return (i);
}