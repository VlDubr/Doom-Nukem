/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   damageenemy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 13:16:08 by gdaniel           #+#    #+#             */
/*   Updated: 2019/05/21 13:25:01 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void		damageenemy(t_player *player, t_object *obj, double delta)
{
	t_fvector2d dist;

	if (obj->isagression)
	{
		dist.x = obj->pos.x - player->pos.x;
		dist.y = obj->pos.z - player->pos.z;
		if (dist.x <= 2 && dist.x >= -2 && dist.y <= 2 && dist.y >= -2)
			minushealth(player, 0.001f * delta);
	}
}
