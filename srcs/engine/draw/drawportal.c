/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawportal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 19:06:08 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/10 19:58:34 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	setwalldown(t_wall *wall, t_sector *sec, t_sector *newsec, int type)
{
	wall->p[0] = setfvector(wall->oldpoint[0].x, sec->floor,
	wall->oldpoint[0].y, 1);
	wall->p[1] = setfvector(wall->oldpoint[1].x, sec->floor,
	wall->oldpoint[1].y, 1);
	wall->p[2] = addfvector(wall->p[0], 0, newsec->floor - sec->floor, 0);
	wall->p[3] = addfvector(wall->p[1], 0, newsec->floor - sec->floor, 0);
	wall->type = type;
}

void	setwallup(t_wall *wall, t_sector *sec, t_sector *newsec, int type)
{
	wall->p[0] = setfvector(wall->oldpoint[0].x,
	newsec->floor + newsec->height,
	wall->oldpoint[0].y, 1);
	wall->p[1] = setfvector(wall->oldpoint[1].x,
	newsec->floor + newsec->height,
	wall->oldpoint[1].y, 1);
	wall->p[2] = addfvector(wall->p[0], 0,
	(sec->floor + sec->height) - (newsec->floor + newsec->height), 0);
	wall->p[3] = addfvector(wall->p[1], 0,
	(sec->floor + sec->height) - (newsec->floor + newsec->height), 0);
	wall->type = type;
}

int		portal(t_doom *doom, t_wall **wall, t_sector *sec, t_sector *newsec)
{
	int i;

	i = 0;
	if (doom->portalvisit[newsec->id] == 0)
	{
		if (sec->floor < newsec->floor)
		{
			setwalldown(&(*wall)[0], sec, newsec, 1);
			i++;
		}
		else if (newsec->floor < sec->floor)
		{
			setwalldown(&(*wall)[0], newsec, sec, 2);
			i++;
		}
		// else if (newsec->floor == sec->floor)
		// 	i++;

		if (sec->height + sec->floor > newsec->height + newsec->floor)
		{
			setwallup(&(*wall)[1], sec, newsec, 4);
			i++;
		}
		else if (newsec->height + newsec->floor > sec->height + sec->floor)
		{
			setwallup(&(*wall)[1], newsec, sec, 5);
			i++;
		}
		// else if (newsec->height == sec->height)
		// 	i++;
	}
	doom->portalvisit[sec->id] = 1;
	return (i);
}
