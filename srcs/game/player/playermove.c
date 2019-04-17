/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playermove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:38:21 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/17 20:26:50 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	checkpos(t_doom *doom, t_fvector newpos, t_fvector2d dir)
{
	size_t		lastsector;

	doom->player.velosity = newpos;
	if (collide(setfvector2d(doom->player.pos.x, doom->player.pos.z),
		setfvector2d(doom->player.velosity.x, doom->player.velosity.z),
		doom->thismap.walls + doom->thismap.sectors[doom->player.sector].start,
		doom->thismap.sectors[doom->player.sector].count))
		return ;
	lastsector = doom->player.sector;
	doom->player.sector = isinside(setfvector2d(doom->player.velosity.x,
	doom->player.velosity.z), doom->thismap, doom->player.sector);
	if (lastsector != doom->player.sector)
		if ((doom->player.velosity.y / 2)
		< doom->thismap.sectors[doom->player.sector].floor)
		{
			doom->player.sector = lastsector;
			return ;
		}
	doom->player.pos = doom->player.velosity;
}

void		playermove(t_doom *doom, double delta)
{
	int			i;
	float		angle;
	t_fvector2d	dir;

	if (doom->input.keystate[SDL_SCANCODE_W])
	{
		angle = doom->player.rotate.z;
	}
	angle = doom->input.keystate[SDL_SCANCODE_D] ||
	doom->input.keystate[SDL_SCANCODE_A] ? doom->player.rotate.z + 1.57f :
	doom->player.rotate.z;
	dir = setfvector2d(cos(angle), sin(angle));
	i = doom->input.keystate[SDL_SCANCODE_W] ||
	doom->input.keystate[SDL_SCANCODE_D] ? 1 : 0;
	if (doom->player.state == 2 && doom->player.stamina > 0)
	{
		dir = multfvector2d(dir, doom->player.runspeed
		* delta, doom->player.runspeed * delta);
		doom->player.stamina--;
	}
	else
		dir = multfvector2d(dir, doom->player.movespeed * delta,
		doom->player.movespeed * delta);
	changepos(doom, i, dir);
}
