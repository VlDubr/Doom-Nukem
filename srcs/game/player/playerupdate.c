/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerupdate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 17:09:31 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/12 17:10:04 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	gravity(t_player *p, float y, double delta)
{
	if (p->pos.y - p->height > y)
		p->pos.y -= 0.02f * delta;
	if (p->pos.y - p->height > y - 0.1f && p->pos.y - p->height < y + 0.1f)
		p->jump = 0;
	if (p->pos.y - p->height < y)
		p->pos.y += 0.02f * delta;
}

void	playerrotate(t_player *p)
{
	if (p->rotate.z > 6.27f)
		p->rotate.z = 0;
	if (p->rotate.z < 0)
		p->rotate.z = 6.27f;
	if (p->rotate.x > 0.79f)
		p->rotate.x = 0.79f;
	if (p->rotate.x < -0.79f)
		p->rotate.x = -0.79f;
}

void	rotate(t_doom *doom, double delta)
{
	if (doom->setting.input.keystate[doom->setting.input.rotright])
		doom->player.rotate.z += 0.005f * delta;
	else if (doom->setting.input.keystate[doom->setting.input.rotleft])
		doom->player.rotate.z -= 0.005f * delta;
	else if (doom->setting.input.keystate[doom->setting.input.rotup])
		doom->player.rotate.x += 0.005f * delta;
	else
		doom->player.rotate.x -= 0.005f * delta;
}
