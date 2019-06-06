/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawpistol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 11:50:03 by gdaniel           #+#    #+#             */
/*   Updated: 2019/05/31 17:06:02 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	drawweapon(t_doom *doom)
{
	if (doom->player.thisweapon->imagetype.x == 1 &&
	doom->player.thisweapon->anim.state == 1)
	{
		drawimage(doom, setirect(setivector2d(400, 400), 400, 400),
		&doom->player.thisweapon->anim.thisframe);
		nextframe(&doom->player.thisweapon->anim);
		if (doom->player.thisweapon->anim.countframe == 0)
			stopanim(&doom->player.thisweapon->anim);
	}
	else
		drawimage(doom, setirect(setivector2d(400, 400), 400, 400),
		&doom->player.thisweapon->texture[0]);
}
