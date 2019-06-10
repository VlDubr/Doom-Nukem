/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pickup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 17:16:17 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/10 17:56:58 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	objpickup(t_input input, t_player *p, t_object *obj)
{
	if (input.keystate[input.use])
	{
		if (obj->isactive && obj->isagression)
		{
			if (obj->typeuse == ADDHEALTH)
				addhealth(p, 10);
			else if (obj->typeuse == ADDAMMO)
			{
				if (p->thisweapon->thisammo + 10 <= p->thisweapon->maxammo)
					p->thisweapon->thisammo += 10;
			}
			else if (obj->typeuse == ADDSTAMIN)
				addstamina(p, 10);
			obj->isactive = 0;
		}
	}
}
