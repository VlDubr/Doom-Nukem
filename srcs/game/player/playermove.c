/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playermove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:38:21 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/11 18:45:03 by gdaniel          ###   ########.fr       */
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
	doom->player.pos = setfvector(newpos.x, doom->player.pos.y, newpos.y);
	doom->player.sector = isinside(newpos, doom->thismap, doom->player);
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
	doom->player.pos = setfvector(newpos.x, doom->player.pos.y, newpos.y);
	doom->player.sector = isinside(newpos, doom->thismap, doom->player);
}

void	playerjump(t_player *player)
{
	player->pos.y = flerp(0, player->maxheightjump,
	(1 / player->maxstamina) * player->stamina);
}

void	playermove(t_player *player, t_fvector2d dir)
{
	if (player->state == 2 && player->stamina > 0)
	{
		dir = multfvector2d(dir, player->runspeed, player->runspeed);
		player->stamina--;
	}
	else
		dir = multfvector2d(dir, player->movespeed, player->movespeed);
	player->velosity = setfvector(dir.x, dir.y, 0);
}
