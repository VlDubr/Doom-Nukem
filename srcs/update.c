/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:41:03 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/23 16:50:37 by gdaniel          ###   ########.fr       */
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
	if (doom->input.keystate[doom->input.rotright])
		doom->player.rotate.z += 0.005f * delta;
	else if (doom->input.keystate[doom->input.rotleft])
		doom->player.rotate.z -= 0.005f * delta;
	else if (doom->input.keystate[doom->input.rotup])
		doom->player.rotate.x += 0.005f * delta;
	else
		doom->player.rotate.x -= 0.005f * delta;
}

void	checkkeyboard(t_doom *doom, double delta)
{
	if (doom->input.keystate[SDL_SCANCODE_RSHIFT] ||
	doom->input.keystate[SDL_SCANCODE_LSHIFT])
		doom->player.run = 1;
	else
		doom->player.run = 0;

	if (doom->input.keystate[SDL_SCANCODE_RCTRL] ||
	doom->input.keystate[SDL_SCANCODE_LCTRL])
		doom->player.height = 2;
	else
		doom->player.height = 5;

	if (doom->input.keystate[doom->input.moveforward] ||
		doom->input.keystate[doom->input.movebackward] ||
		doom->input.keystate[doom->input.moveleft] ||
		doom->input.keystate[doom->input.moveright])
		playermove(doom, delta);

	if (doom->input.keystate[doom->input.rotleft] ||
	doom->input.keystate[doom->input.rotright] ||
	doom->input.keystate[doom->input.rotup] ||
	doom->input.keystate[doom->input.rotdown])
		rotate(doom, delta);

	if ((!doom->player.jump) && doom->input.keystate[doom->input.jump] &&
	doom->player.stamina > 0)
		playerjump(doom, &doom->player);

	if (doom->input.keystate[SDL_SCANCODE_ESCAPE])
		doom->win->state = 0;

	if (doom->input.keystate[SDL_SCANCODE_P])
		printf("pos: %f %f %f\n", doom->player.pos.x, doom->player.pos.y, doom->player.pos.z);

	if (doom->player.velosity.x == 0 || doom->player.velosity.y == 0 ||
	doom->player.velosity.z == 0)
		addstamina(&doom->player, 0.1f);
	doom->player.velosity = setfvector(0, 0, 0, 0);
}

void	update(t_doom *doom, double delta)
{
	checkkeyboard(doom, delta);
	playerrotate(&doom->player);
	gravity(&doom->player,
	doom->thismap.sectors[doom->player.sector].floor, delta);
	checkswaplevel(doom, doom->player.sector);
}
