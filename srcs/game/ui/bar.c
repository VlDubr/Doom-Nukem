/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bar.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 19:14:29 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/03 19:14:32 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_bar		setbar(t_rgba color, t_fvector2d pos, t_fvector2d wh)
{
	t_bar	r;

	r.color = color;
	r.pos = pos;
	r.widthheight = wh;
	return (r);
}

void		drawbar(uint32_t *p, t_bar bar)
{
	t_ivector2d cord;

	if (p != NULL)
	{
		cord.y = (int)bar.pos.y;
		while (cord.y < bar.pos.y + bar.widthheight.y)
		{
			cord.x = (int)bar.pos.x;
			while (cord.x < bar.pos.x + bar.widthheight.x)
			{
				drawpoint(p, setivector2d(800, 600), cord, bar.color);
				cord.x++;
			}
			cord.y++;
		}
	}
}
