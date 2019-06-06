/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawpoint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 19:11:44 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/03 19:12:00 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	drawpoint(uint32_t *p, t_ivector2d size, t_ivector2d cord,
t_rgba color)
{
	t_rgba		pc;
	t_rgba		newc;
	uint32_t	c;

	c = p[cord.x + ((cord.y) * 800)];
	pc.alpha = c >> 24;
	pc.red = ((c << 8) >> 24);
	pc.green = ((c << 16) >> 24);
	pc.blue = ((c << 24) >> 24);
	c = ((((((color.alpha << 8) | color.red) << 8) | color.green) << 8)
	| color.blue);
	if (color.alpha == 255)
	{
		if (cord.x >= 0 && cord.x < size.x && cord.y >= 0 && cord.y < size.y)
			p[cord.x + ((cord.y) * 800)] = c;
	}
	else if (color.alpha < 255 && color.alpha > 0)
	{
		newc = opacityrgba(pc, color);
		p[cord.x + ((cord.y) * 800)] = ((((((newc.alpha << 8) | newc.red) << 8)
		| newc.green) << 8) | newc.blue);
	}
}
