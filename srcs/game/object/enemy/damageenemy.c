/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   damageenemy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 13:16:08 by gdaniel           #+#    #+#             */
/*   Updated: 2019/05/22 14:16:42 by gdaniel          ###   ########.fr       */
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
		if (dist.x <= 5 && dist.x >= -5 && dist.y <= 5 && dist.y >= -5)
			minushealth(player, 0.001f * delta);
	}
}
