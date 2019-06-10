/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   agression.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:27:33 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/10 17:36:21 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	agressionememy(t_player *player, t_object *obj)
{
	t_fvector2d dist;

	dist.x = obj->pos.x - player->pos.x;
	dist.y = obj->pos.z - player->pos.z;
	if (dist.x <= obj->agressionarea && dist.x >= -obj->agressionarea &&
	dist.y <= obj->agressionarea && dist.y >= -obj->agressionarea)
	{
		obj->isagression = 1;
		if (!(dist.x >= -4 && dist.x <= 4 && dist.y >= -4 && dist.y <= 4))
			obj->ismove = 1;
		else
			obj->ismove = 0;
	}
	else
	{
		obj->isagression = 0;
		obj->ismove = 0;
		obj->dsc = obj->dscmax;
	}
}
