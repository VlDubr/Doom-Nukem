/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawimage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 11:42:13 by gdaniel           #+#    #+#             */
/*   Updated: 2019/05/31 16:03:55 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	drawimage(t_doom *doom, t_irect rect, t_tga *image)
{
	t_fvector2d	uv;
	t_ivector2d cord;
	t_fvector2d step;
	t_rgba		color;

	cord.y = rect.start.y;
	uv.y = 0;
	step.x = (float)image->width / rect.width;
	step.y = (float)image->height / rect.height;
	while (cord.y < rect.start.y + rect.height)
	{
		cord.x = rect.start.x;
		uv.x = 0;
		while (cord.x < rect.start.x + rect.width)
		{
			color = image->pic[(int)uv.y][(int)uv.x];
			drawpoint(doom->win->pixels, doom->win->size, cord, color);
			uv.x += step.x;
			cord.x++;
		}
		uv.y += step.y;
		cord.y++;
	}
}
