/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightmod.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 17:59:43 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/10 18:06:03 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	lightmod(t_object *obj, t_map *map, t_input input)
{
	if (obj->isactive && obj->isagression && input.keystate[input.use])
	{
		if (map->sectors[obj->sector].light == 1)
			map->sectors[obj->sector].light = 0.2f;
		else
			map->sectors[obj->sector].light = 1;
	}
}
