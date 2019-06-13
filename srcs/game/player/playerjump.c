/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerjump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 11:43:51 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/13 17:59:11 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	playerjump(t_doom *doom, t_player *player)
{
	float	height;

	Mix_PlayChannel(2, doom->sound.jump, 0);
	height = doom->thismap.sectors[player->sector].floor +
	doom->thismap.sectors[player->sector].height >
	doom->thismap.sectors[player->sector].floor + player->maxheightjump ?
	doom->thismap.sectors[player->sector].floor + player->maxheightjump :
	doom->thismap.sectors[player->sector].floor +
	doom->thismap.sectors[player->sector].height;
	player->pos.y = flerp(doom->thismap.sectors[player->sector].floor +
	player->height, height,
	(1 / player->maxstamina) * player->stamina);
	minusstamina(player, 20);
	player->jump = 1;
}
