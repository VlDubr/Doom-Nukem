/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 19:09:06 by gdaniel           #+#    #+#             */
/*   Updated: 2019/05/31 18:11:27 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	shot(t_doom *doom, Mix_Chunk *s)
{
	if (doom->setting.input.mousekey[0])
	{
		if (doom->player.thisweapon->thisammo > 0)
		{
			startanim(&doom->weapons[0].anim);
			if (doom->player.targetid != 18446744073709551615u)
				doom->thismap.obj[doom->player.targetid].health -= 10;
			doom->player.thisweapon->thisammo--;
			Mix_PlayChannel(2, s, 0);
		}
	}
}
