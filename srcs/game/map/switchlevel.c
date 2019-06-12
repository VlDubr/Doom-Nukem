/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switchlevel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 16:50:24 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/12 12:59:16 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	switchlevel(t_doom *doom, size_t level)
{
	size_t c;

	c = 0;
	if (level < doom->mapcount)
	{
		doom->thismap = doom->maps[level];
		doom->player.sector = isinside(
		setfvector2d(doom->thismap.startplayer.pos.x,
		doom->thismap.startplayer.pos.z), doom->thismap, 0);
		while (c < doom->thismap.objcount)
		{
			doom->thismap.obj[c].sector = isinside(
			setfvector2d(doom->thismap.obj[c].pos.x,
			doom->thismap.obj[c].pos.z), doom->thismap, 0);
			c++;
		}
		doom->player.pos = doom->thismap.startplayer.pos;
		doom->player.pos.y = doom->thismap.sectors[doom->player.sector].floor
		+ doom->player.height;
		doom->player.rotate = doom->thismap.startplayer.rotate;
		doom->player.health = doom->player.maxhealth;
	}
}
