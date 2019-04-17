/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:41:03 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/17 12:39:47 by gdaniel          ###   ########.fr       */
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

void	playerzpos(t_player *p, float y, double delta)
{
	if (p->pos.y - p->height >= y)
		p->pos.y -= 0.005f * delta;
	if (p->pos.y - p->height < y)
		p->pos.y += 0.005f * delta;
}

void	playerrotate(t_player *p)
{
	if (p->rotate.z > 6.27f)
		p->rotate.z = 0;
	if (p->rotate.z < 0)
		p->rotate.z = 6.27f;
	if (p->rotate.x > 1.57f)
		p->rotate.x = 1.57f;
	if (p->rotate.x < -1.57f)
		p->rotate.x = -1.57f;
}

void	rotate(t_doom *doom, double delta)
{
	if (doom->input.keystate[SDL_SCANCODE_RIGHT])
		doom->player.rotate.z += 0.005f * delta;
	else
		doom->player.rotate.z -= 0.005f * delta;
	// else if (key == doom->input.rotup)
	// 	doom->player.rotate.x += 0.05f;
	// else
	// 	doom->player.rotate.x -= 0.05f;
}

void	checkkeyboard(t_doom *doom, double delta)
{
	if (doom->input.keystate[SDL_SCANCODE_RSHIFT] || doom->input.keystate[SDL_SCANCODE_LSHIFT])
		doom->player.state |= 2;
	else
		doom->player.state = 0;
	if (doom->input.keystate[doom->input.moveforward] ||
		doom->input.keystate[doom->input.movebackward] ||
		doom->input.keystate[doom->input.moveleft] ||
		doom->input.keystate[doom->input.moveright])
		playermove(doom, delta);
	if (doom->input.keystate[doom->input.rotleft] ||
	doom->input.keystate[doom->input.rotright])
		rotate(doom, delta);
	if (doom->input.keystate[doom->input.jump])
		playerjump(&doom->player);
	if (doom->input.keystate[SDL_SCANCODE_ESCAPE])
		doom->win->state = 0;
}

void	update(t_doom *doom, double delta)
{
	checkkeyboard(doom, delta);
	playerrotate(&doom->player);
	playerzpos(&doom->player,
	doom->thismap.sectors[doom->player.sector].floor, delta);
	if (!(doom->player.state & 2))
		addstamina(&doom->player, 1);
	checkswaplevel(doom, doom->player.sector);
}
