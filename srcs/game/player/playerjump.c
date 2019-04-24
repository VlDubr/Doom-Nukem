/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerjump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 11:43:51 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/24 15:42:07 by gdaniel          ###   ########.fr       */
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
	minusstamina(player, 20);
	player->jump = 1;
}
