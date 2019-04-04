/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playermove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:38:21 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/04 17:49:24 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	playerjump(t_player *player)
{
	player->velosity.z = flerp(0, player->maxheightjump,
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
	player->velosity = setfvector(dir.x, dir.y, 0);
}
