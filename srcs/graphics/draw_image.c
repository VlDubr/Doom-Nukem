/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:18:49 by srafe             #+#    #+#             */
/*   Updated: 2019/06/10 16:00:53 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/editor.h"

void	drawimage(t_sdl *sdl, int xy[2], int wh[2], t_tga *image)
{
	t_fvector2d	uv;
	t_ivector2d cord;
	t_fvector2d step;

	cord.y = xy[1];
	uv.y = 0;
	step.x = (float)image->width / wh[0];
	step.y = (float)image->height / wh[1];
	while (cord.y < xy[1] + wh[1])
	{
		cord.x = xy[0];
		uv.x = 0;
		while (cord.x < xy[0] + wh[0])
		{
			SDL_SetRenderDrawColor(sdl->r, image->pic[(int)uv.y][(int)uv.x].red,
							image->pic[(int)uv.y][(int)uv.x].green,
							image->pic[(int)uv.y][(int)uv.x].blue,
							image->pic[(int)uv.y][(int)uv.x].alpha);
			SDL_RenderDrawPoint(sdl->r, cord.x, cord.y);
			uv.x += step.x;
			cord.x++;
		}
		uv.y += step.y;
		cord.y++;
	}
}
