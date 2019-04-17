/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerjump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 11:43:51 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/17 11:44:06 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	playerjump(t_player *player)
{
	player->pos.y = flerp(0, player->maxheightjump,
	(1 / player->maxstamina) * player->stamina);
}
