/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawceil.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 19:12:43 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/03 19:12:46 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	drawceil(uint32_t *p, t_wall wa, t_rgb color)
{
	float	endy;
	float	y;
	int		x;
	int		i;

	if (wa.p[0].x > wa.p[1].x)
		ft_swap((void**)&wa.p[0], (void**)&wa.p[1]);
	x = wa.p[0].x;
	i = 0;
	while (x < wa.p[1].x)
	{
		y = 0;
		endy = flerp(wa.p[0].y, wa.p[1].y, ((float)1 /
		(wa.p[1].x - wa.p[0].x)) * i);
		while (y < endy)
		{
			if (x >= 0 && x < 800 && y >= 0 && y < 600)
				p[(int)x + ((int)y * 800)] = ((((((255 << 8) |
				color.red) << 8) |
				color.green) << 8) | color.blue);
			y++;
		}
		i++;
		x++;
	}
}
