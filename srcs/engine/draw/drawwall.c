/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawwall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 18:29:39 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/08 16:08:23 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	drawwall(SDL_Renderer *r, t_drawwall w)
{
	t_fvector2d cord;
	t_fvector2d	end;
	float		delta;
	int			i;

	if (w.p[0].x < 0)
	{
		cord.x = 0;
		i = fabsf(cord.x - w.p[0].x);
	}
	else
	{
		cord.x = w.p[0].x;
		i = 0;
	}
	cord.x = cord.x > 800 ? 800 : cord.x;
	end.x = w.p[1].x > 800 ? 800 : w.p[1].x;
	while (cord.x < end.x)
	{
		cord.y = flerp(w.p[2].y, w.p[3].y, (((float)1 / (w.p[1].x - w.p[0].x)) * i)) < 0 ? 0 :
		flerp(w.p[2].y, w.p[3].y, (((float)1 / (w.p[1].x - w.p[0].x)) * i));
		end.y = flerp(w.p[0].y, w.p[1].y, (((float)1 / (w.p[1].x - w.p[0].x)) * i));
		while (cord.y < end.y)
		{
			SDL_RenderDrawPoint(r, cord.x, cord.y);
			cord.y++;
		}
		i++;
		cord.x++;
	}
}
