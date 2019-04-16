/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playermove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:38:21 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/15 20:01:00 by gdaniel          ###   ########.fr       */
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

void	moveplayer(t_player	*player, t_map map, float rotoffset, int i)
{
	t_fvector2d	dir;
	size_t		lastsector;

	dir.x = cos(player->rotate.z + rotoffset);
	dir.y = sin(player->rotate.z + rotoffset);
	player->velocity = i ? addfvector(player->pos, dir.x , 0, dir.z) :
	subfvector(player->pos, dir.x , 0, dir.z);
	if (//Collide)
		return ;
	lastsector = player->sector;
	player->sector = //inside;
	if (lastsector != player->sector)
		if (!(player.velocity.z + player->height > map.sector[player->sector].floor))
			return ;
	player->pos = player->velocity;
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
	player->velosity = setfvector(dir.x, dir.y, 0, 1);
}
