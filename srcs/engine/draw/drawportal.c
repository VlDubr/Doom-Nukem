/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawportal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 19:06:08 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/11 14:39:25 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	setwalldown(t_list **wall, t_sector *sec, t_sector *newsec,
t_fvector oldpoint[3])
{
	t_wall *wa;

	if ((wa = (t_wall*)malloc(sizeof(t_wall))) == NULL)
		error("Error: mamore not allocated");
	wa->p[0] = setfvector(oldpoint[0].x, sec->floor,
	oldpoint[0].y, 1);
	wa->p[1] = setfvector(oldpoint[1].x, sec->floor,
	oldpoint[1].y, 1);
	wa->p[2] = addfvector(wa->p[0], 0, newsec->floor - sec->floor, 0);
	wa->p[3] = addfvector(wa->p[1], 0, newsec->floor - sec->floor, 0);
	wa->type = (int)oldpoint[2].x;
	addwallinlist(wall, *wa);
	free(wa);
}

void	setwallup(t_list **wall, t_sector *sec, t_sector *newsec,
t_fvector oldpoint[3])
{
	t_wall *wa;

	if ((wa = (t_wall*)malloc(sizeof(t_wall))) == NULL)
		error("Error: mamore not allocated");
	wa->p[0] = setfvector(oldpoint[0].x,
	newsec->floor + newsec->height, oldpoint[0].y, 1);
	wa->p[1] = setfvector(oldpoint[1].x,
	newsec->floor + newsec->height, oldpoint[1].y, 1);
	wa->p[2] = addfvector(wa->p[0], 0,
	(sec->floor + sec->height) - (newsec->floor + newsec->height), 0);
	wa->p[3] = addfvector(wa->p[1], 0,
	(sec->floor + sec->height) - (newsec->floor + newsec->height), 0);
	wa->type = (int)oldpoint[2].x;
	addwallinlist(wall, *wa);
	free(wa);
}

void	setdoorwall(t_list **wall, t_sector *sec, t_sector *newsec,
t_fvector oldpoint[3])
{
	t_wall *wa;

	if ((wa = (t_wall*)malloc(sizeof(t_wall))) == NULL)
		error("Error: mamore not allocated");
	wa->p[0] = setfvector(oldpoint[0].x, newsec->floor, oldpoint[0].y, 1);
	wa->p[1] = setfvector(oldpoint[1].x, newsec->floor, oldpoint[1].y, 1);
	wa->p[2] = setfvector(oldpoint[0].x, sec->floor +
	sec->height, oldpoint[0].y, 1);
	wa->p[3] = setfvector(oldpoint[1].x, sec->floor +
	sec->height, oldpoint[1].y, 1);
	wa->type = 6;
	addwallinlist(wall, *wa);
	free(wa);
}

void	drawup(t_list **wall, t_sector *sec, t_sector *newsec, t_fvector old[3])
{
	if (sec->floor < newsec->floor)
	{
		old[2].x = 3;
		setwalldown(wall, sec, newsec, old);
	}
	else if (newsec->floor < sec->floor)
	{
		old[2].x = 2;
		setwalldown(wall, newsec, sec, old);
	}
}

void	portal(t_doom *doom, t_list **wall, t_sector *sec, t_fvector old[3])
{
	t_sector newsec;

	newsec = doom->thismap.sectors[(int)old[0].z];
	if (doom->portalvisit[newsec.id] == 0)
	{
		drawup(wall, sec, &newsec, old);
		if (sec->height + sec->floor > newsec.height + newsec.floor)
		{
			old[2].x = 4;
			setwallup(wall, sec, &newsec, old);
		}
		else if (newsec.height + newsec.floor > sec->height + sec->floor)
		{
			old[2].x = 5;
			setwallup(wall, &newsec, sec, old);
		}
		if (old[0].w == 1)
			setdoorwall(wall, sec, &newsec, old);
	}
	doom->portalvisit[sec->id] = 1;
}
