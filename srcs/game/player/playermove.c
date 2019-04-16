/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playermove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:38:21 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/16 12:59:33 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	movelr(SDL_Keycode key, t_doom *doom)
{
	t_fvector2d	pos;
	t_fvector2d	newpos;
	t_fvector2d	dir;

	dir = retnewpos(doom->player.rotate.z + 1.57f);
	pos = setfvector2d(doom->player.pos.x, doom->player.pos.z);
	newpos = key == doom->input.moveright ? addfv2dtofv2d(pos, dir) : subfv2dtofv2d(pos, dir);
	if (collide(pos, newpos, doom->thismap.walls +
	doom->thismap.sectors[doom->player.sector].start,
	doom->thismap.sectors[doom->player.sector].count))
		return ;
	doom->player.pos = setfvector(newpos.x, doom->player.pos.y, newpos.y, 1);
	doom->player.sector = isinside(newpos, doom->thismap, doom->player.sector);
}

void	movefb(SDL_Keycode key, t_doom *doom)
{
	t_fvector2d	pos;
	t_fvector2d	newpos;
	t_fvector2d	dir;

	dir = retnewpos(doom->player.rotate.z);
	pos = setfvector2d(doom->player.pos.x, doom->player.pos.z);
	newpos = key == doom->input.moveforward ? addfv2dtofv2d(pos, dir) : subfv2dtofv2d(pos, dir);
	if (collide(pos, newpos, doom->thismap.walls +
	doom->thismap.sectors[doom->player.sector].start,
	doom->thismap.sectors[doom->player.sector].count))
		return ;
	doom->player.pos = setfvector(newpos.x, doom->player.pos.y, newpos.y, 1);
	doom->player.sector = isinside(newpos, doom->thismap, doom->player.sector);
}

void	moveplayer(t_doom *doom, int i, t_fvector2d dir)
{
	size_t		lastsector;

	if (i)
		doom->player.velosity = addfvector(doom->player.pos, dir.x , 0, dir.y);
	else
		doom->player.velosity = subfvector(doom->player.pos, dir.x , 0, dir.y);

	if (collide(setfvector2d(doom->player.pos.x, doom->player.pos.z),
		setfvector2d(doom->player.velosity.x, doom->player.velosity.z),
		doom->thismap.walls + doom->thismap.sectors[doom->player.sector].start,
		doom->thismap.sectors[doom->player.sector].count))
		return ;
	lastsector = doom->player.sector;
	doom->player.sector = isinside(setfvector2d(doom->player.velosity.x,
	doom->player.velosity.z), doom->thismap, doom->player.sector);
	if (lastsector != doom->player.sector)
		if ((doom->player.velosity.y / 2) < doom->thismap.sectors[doom->player.sector].floor)
		{
			doom->player.sector = lastsector;
			return ;
		}
	doom->player.pos = doom->player.velosity;
}

void	playerjump(t_player *player)
{
	player->pos.y = flerp(0, player->maxheightjump,
	(1 / player->maxstamina) * player->stamina);
}

void	playermove(t_doom *doom)
{
	int			i;
	t_fvector2d	dir;

	if (doom->input.keystate[SDL_SCANCODE_D] ||
	doom->input.keystate[SDL_SCANCODE_A])
	{
		dir.x = cos(doom->player.rotate.z + 1.57f);
		dir.y = sin(doom->player.rotate.z + 1.57f);
	}
	else
	{
		dir.x = cos(doom->player.rotate.z);
		dir.y = sin(doom->player.rotate.z);
	}
	i = doom->input.keystate[SDL_SCANCODE_W] ||
	doom->input.keystate[SDL_SCANCODE_D] ? 1 : 0;
	if (doom->player.state == 2 && doom->player.stamina > 0)
	{
		dir = multfvector2d(dir, doom->player.runspeed, doom->player.runspeed);
		doom->player.stamina--;
	}
	else
		dir = multfvector2d(dir, doom->player.movespeed, doom->player.movespeed);
	moveplayer(doom, i, dir);
}
