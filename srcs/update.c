/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:41:03 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/09 18:01:45 by gdaniel          ###   ########.fr       */
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

void	playerzpos(t_player *p, float y)
{
	if (p->pos.y - p->height >= y)
		p->pos.y -= 0.08f;
	if (p->pos.y - p->height < y)
		p->pos.y += 0.08f;
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

void	update(t_doom *doom)
{
	playerrotate(&doom->player);
	playerzpos(&doom->player, doom->thismap.sectors[doom->player.sector].floor);
	checkswaplevel(doom, doom->player.sector);
}
