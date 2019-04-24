/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerjump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 11:43:51 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/24 15:19:23 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	playerjump(t_doom *doom, t_player *player)
{
	float	height;
	float	tmp;

	height = doom->thismap.sectors[player->sector].floor +
	doom->thismap.sectors[player->sector].height >
	doom->thismap.sectors[player->sector].floor + player->maxheightjump ?
	doom->thismap.sectors[player->sector].floor + player->maxheightjump :
	doom->thismap.sectors[player->sector].floor +
	doom->thismap.sectors[player->sector].height;
	tmp = player->pos.y;
	player->pos.y = flerp(doom->thismap.sectors[player->sector].floor +
	player->height, height,
	(1 / player->maxstamina) * player->stamina);
	if (tmp != player->pos.y)
		Mix_PlayChannel(1, doom->sounds->samples[0], 0);
	minusstamina(player, 20);
	player->jump = 1;
}
