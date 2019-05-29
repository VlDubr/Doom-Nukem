/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   damageenemy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 13:16:08 by gdaniel           #+#    #+#             */
/*   Updated: 2019/05/29 19:07:28 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void		damageenemy(Mix_Chunk *s, t_player *player, t_object *obj, double delta)
{
	t_fvector2d dist;

	if (obj->isagression)
	{
		dist.x = obj->pos.x - player->pos.x;
		dist.y = obj->pos.z - player->pos.z;
		if (dist.x <= 5 && dist.x >= -5 && dist.y <= 5 && dist.y >= -5)
		{
			obj->dsc++;
			if (obj->dsc >= obj->dscmax)
			{
				Mix_PlayChannel(3, s, 0);
				minushealth(player, ((float)obj->damage / 1) * delta);
				obj->dsc = 0;
			}
		}
	}
}
