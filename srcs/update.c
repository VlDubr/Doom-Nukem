/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:41:03 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/04 12:45:13 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	checkswaplevel(t_doom *doom, size_t secid)
{
	if (doom->thismap.sectors[secid].type == 1)
	{
		doom->level++;
		if (doom->level < doom->mapcount)
			switchlevel(doom, doom->level);
		else
			doom->win->state = 0;
	}
}

void	gravity(t_player *p, float y, double delta)
{
	if (p->pos.y - p->height > y)
		p->pos.y -= 0.02f * delta;
	if (p->pos.y - p->height > y - 0.1f && p->pos.y - p->height < y + 0.1f)
		p->jump = 0;
	if (p->pos.y - p->height < y)
		p->pos.y += 0.02f * delta;
}

void	playerrotate(t_player *p)
{
	if (p->rotate.z > 6.27f)
		p->rotate.z = 0;
	if (p->rotate.z < 0)
		p->rotate.z = 6.27f;
	if (p->rotate.x > 0.79f)
		p->rotate.x = 0.79f;
	if (p->rotate.x < -0.79f)
		p->rotate.x = -0.79f;
}

void	rotate(t_doom *doom, double delta)
{
	if (doom->setting.input.keystate[doom->setting.input.rotright])
		doom->player.rotate.z += 0.005f * delta;
	else if (doom->setting.input.keystate[doom->setting.input.rotleft])
		doom->player.rotate.z -= 0.005f * delta;
	else if (doom->setting.input.keystate[doom->setting.input.rotup])
		doom->player.rotate.x += 0.005f * delta;
	else
		doom->player.rotate.x -= 0.005f * delta;
}

void	checkrun(t_doom *doom)
{
	if (doom->setting.input.keystate[SDL_SCANCODE_RSHIFT] ||
	doom->setting.input.keystate[SDL_SCANCODE_LSHIFT])
		doom->player.run = 1;
	else
		doom->player.run = 0;
}

void	checkmove(t_doom *doom, double delta)
{
	if (doom->setting.input.keystate[doom->setting.input.moveforward] ||
		doom->setting.input.keystate[doom->setting.input.movebackward] ||
		doom->setting.input.keystate[doom->setting.input.moveleft] ||
		doom->setting.input.keystate[doom->setting.input.moveright])
		playermove(doom, delta);
}

void	checkkeyboard(t_doom *doom, double delta)
{
	checkrun(doom);
	if (doom->setting.input.keystate[SDL_SCANCODE_RCTRL] ||
	doom->setting.input.keystate[SDL_SCANCODE_LCTRL])
		doom->player.height = 2;
	else
		doom->player.height = 5;
	checkmove(doom, delta);
	if (doom->setting.input.keystate[doom->setting.input.jump] &&
	doom->player.stamina > 0)
		playerjump(doom, &doom->player);
	if (doom->setting.input.keystate[SDL_SCANCODE_ESCAPE])
		doom->win->state = 0;
	shot(doom, doom->sound.shot);
	if (doom->player.velosity.x == 0 || doom->player.velosity.y == 0 ||
	doom->player.velosity.z == 0)
		addstamina(&doom->player, 0.1f);
	
	if (doom->setting.input.keystate[SDL_SCANCODE_P])
	{
		printf("pos: x %f y %f z %f\n", doom->player.pos.x, doom->player.pos.y, doom->player.pos.z);
		printf("rot: x %f y %f z %f\n", doom->player.rotate.x, doom->player.rotate.y, doom->player.rotate.z);
	}
	doom->player.velosity = setfvector(0, 0, 0, 0);
}

void	update(t_doom *doom, double delta)
{
	size_t c;

	c = 0;
	checkkeyboard(doom, delta);
	playerrotate(&doom->player);
	gravity(&doom->player,
	doom->thismap.sectors[doom->player.sector].floor, delta);
	checkswaplevel(doom, doom->player.sector);
	while (c < doom->thismap.objcount)
	{
		agressionememy(&doom->player, &doom->thismap.obj[c]);
		damageenemy(doom->sound.run, &doom->player,
		&doom->thismap.obj[c], delta);
		moveenemy(doom, &doom->thismap.obj[c], delta);
		c++;
	}
	doom->player.targetid = 18446744073709551615u;
	updateui(doom);
}
