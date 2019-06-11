/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opendoor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 19:38:50 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/11 12:37:57 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	opendoor(t_object *obj, t_input input, t_map *map)
{
	if (obj->isactive && obj->isagression && input.keystate[input.use])
	{
		if (map->walls[obj->typeuse].w == 1)
			map->walls[obj->typeuse].w = 0;
		else
			map->walls[obj->typeuse].w = 1;
		obj->isactive = 0;
	}
}
