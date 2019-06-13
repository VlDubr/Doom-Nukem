/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brez.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:58:20 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/13 16:58:41 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	drawpointwall(t_wall wall, t_fvector2d cord, t_rgba color, uint32_t *p)
{
	t_rgba		pc;
	t_rgba		newc;
	uint32_t	c;
	int			l;

	l = wall.light == 1 ? 2 : 1;
	c = p[(int)cord.x + (((int)cord.y) * 800)];
	pc.alpha = c >> 24;
	pc.red = (((c << 8) >> 24));
	pc.green = (((c << 16) >> 24));
	pc.blue = (((c << 24) >> 24));
	if (color.alpha == 255)
	{
		if (cord.x >= 0 && cord.x < 800 && cord.y >= 0 && cord.y < 800)
			p[(int)cord.x + (((int)cord.y) * 800)] =
			((((((color.alpha << 8) | color.red / l) << 8) |
			color.green / l) << 8) | color.blue / l);
	}
	else if (color.alpha < 255 && color.alpha > 0)
	{
		newc = opacityrgba(pc, color);
		p[(int)cord.x + (((int)cord.y) * 800)] =
		((((((newc.alpha << 8) | newc.red / l) << 8) |
		newc.green / l) << 8) | newc.blue / l);
	}
}

void	loopbrez(t_drawwallservice walls, int xc, uint32_t *p)
{
	int			yp;

	while (walls.cord.y <= walls.stena[1][xc] &&
	walls.cord.y >= walls.stena[3][xc])
	{
		if ((walls.start == 2 && walls.cord.y >= 800) ||
		(walls.start == 1 && walls.cord.y < 0))
			break ;
		if ((walls.start == 1 && walls.cord.y >= 800))
			walls.cord.y = 800;
		if ((walls.start == 2 && walls.cord.y < 0))
			walls.cord.y = 0;
		walls.cord.y += walls.keey.z;
		walls.ddd.z += walls.ddd.z < 0 ? walls.ddd.x : walls.ddd.y;
		if (walls.ddd.z >= 0)
			walls.cord.x += walls.keey.y;
		yp = (int)((walls.cord.y - walls.stena[3][xc]) / walls.keey.x);
		if (yp >= 0 && yp < walls.wall.texture.height &&
		walls.xp >= 0 && walls.xp < walls.wall.texture.width &&
		(walls.cord.x >= 0 && walls.cord.x < 800 &&
		walls.cord.y >= 0 && walls.cord.y < 800))
			drawpointwall(walls.wall, walls.cord,
			walls.wall.texture.pic[yp][walls.xp], p);
	}
}

void	brez(t_drawwallservice walls, int xc, t_wall wall, uint32_t *p)
{
	walls.keey.y = 1;
	walls.cord.x = walls.stena[0][xc];
	walls.cord.y = walls.stena[1][xc];
	walls.deltaxy.x = fabs(walls.stena[2][xc] - walls.stena[0][xc]);
	walls.deltaxy.y = fabs(walls.stena[3][xc] - walls.stena[1][xc]);
	walls.ddd.z = 2 * (walls.deltaxy.x - walls.deltaxy.y);
	walls.ddd.x = 2 * walls.deltaxy.x;
	walls.ddd.y = (walls.deltaxy.x - walls.deltaxy.y) * 2.0;
	walls.keey.z = -1;
	if (walls.stena[2][xc] < walls.stena[0][xc])
		walls.keey.y = -1;
	if (walls.start == 2)
	{
		walls.cord.y = walls.stena[3][xc];
		walls.cord.x = walls.stena[2][xc];
		walls.keey.z = 1;
	}
	if (walls.keey.z == 1)
		walls.keey.y *= -1;
	walls.keey.x = walls.deltaxy.y / (wall.texture.height);
	loopbrez(walls, xc, p);
}
