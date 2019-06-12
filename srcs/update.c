/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:41:03 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/12 17:22:24 by gdaniel          ###   ########.fr       */
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
	doom->player.velosity = setfvector(0, 0, 0, 0);
}

void	update(t_doom *doom, double delta)
{
	checkkeyboard(doom, delta);
	playerrotate(&doom->player);
	gravity(&doom->player,
	doom->thismap.sectors[doom->player.sector].floor, delta);
	checkswaplevel(doom, doom->player.sector);
	objectupdate(doom);
	doom->player.targetid = 18446744073709551615u;
	playerdeath(&doom->player, &doom->gamestate);
}
