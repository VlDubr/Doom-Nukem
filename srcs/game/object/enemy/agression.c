/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   agression.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:27:33 by gdaniel           #+#    #+#             */
/*   Updated: 2019/05/15 18:43:54 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		isagression(t_fvector2d dist)
{
	if (dist.x <= 15 && dist.x >= -15 && dist.y <= 15 && dist.y >= -15)
	{
		if (dist.x >= -1 && dist.x <= 1 && dist.y >= -1 && dist.y <= 1)
			return (0);
		else
			return (1);
	}
	return (0);
}

void	agressionememy(t_player *player, t_object *obj)
{
	t_fvector2d dist;

	dist.x = obj->pos.x - player->pos.x;
	dist.y = obj->pos.y - player->pos.y;
	if (dist.x <= 15 && dist.x >= -15 && dist.y <= 15 && dist.y >= -15)
		obj->isagression = 1;
	else
		obj->isagression = 0;
}
