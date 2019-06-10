/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawskybox.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 15:23:30 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/10 15:45:27 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	drawskubox(t_doom *doom)
{
	t_ivector2d	cord;
	t_fvector2d	step;
	t_fvector2d	uv;
	t_rgba		color;

	cord.y = 0;
	uv.y = 0;
	step.y = ((float)doom->skybox->height / doom->win->size.y);
	step.x = 1;
	while (cord.y < doom->win->size.y)
	{
		uv.x = ((float)doom->skybox->width / 6.27f) * doom->player.rotate.z;
		cord.x = 0;
		while (cord.x < doom->win->size.x)
		{
			color = doom->skybox->pic[(int)uv.y][(int)uv.x];
			drawpoint(doom->win->pixels, doom->win->size, cord, color);
			uv.x += step.x;
			cord.x++;
		}
		uv.y += step.y;
		cord.y++;
	}
}
