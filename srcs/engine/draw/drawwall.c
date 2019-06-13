/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawwall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:52:17 by vmcclure          #+#    #+#             */
/*   Updated: 2019/06/13 16:58:31 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "doom.h"

void	mallocstena(t_drawwallservice *walls, t_wall wall)
{
	int	y;

	walls->stena[0] = (float *)malloc((sizeof(float)) *
	(walls->maxmindist.x + 1));
	walls->stena[1] = (float *)malloc((sizeof(float)) *
	(walls->maxmindist.x + 1));
	walls->stena[2] = (float *)malloc((sizeof(float)) *
	(walls->maxmindist.x + 1));
	walls->stena[3] = (float *)malloc((sizeof(float)) *
	(walls->maxmindist.x + 1));
	y = 0;
	while (y < walls->maxmindist.x)
	{
		walls->stena[0][y] = wall.p[0].x + (y * walls->shag.y);
		walls->stena[1][y] = wall.p[0].y + (y * walls->shag.y *
		((float)walls->dist.x / (float)walls->d1d4.start.x)) *
		sin(atan((float)walls->d1d4.start.y / (float)walls->d1d4.start.x));
		walls->stena[2][y] = wall.p[2].x + (y * walls->shag.x);
		walls->stena[3][y] = wall.p[2].y + (y * walls->shag.x *
		((float)walls->dist.y / (float)walls->d1d4.width)) *
		sin(atan((float)walls->d1d4.height / (float)walls->d1d4.width));
		y++;
	}
}

int		checkwallinwindowarea(t_wall wall)
{
	return (wall.p[0].x > 810 || wall.p[1].x > 810
	|| wall.p[0].x < -2 || wall.p[1].x < -2);
}

void	setwallsdist(t_drawwallservice *walls, t_wall wall)
{
	walls->d1d4 = setirect(setivector2d((wall.p[1].x - wall.p[0].x),
	(wall.p[1].y - wall.p[0].y)), (wall.p[3].x - wall.p[2].x),
	(wall.p[3].y - wall.p[2].y));
	walls->dist.x = pow(pow(wall.p[0].x - wall.p[1].x, 2) +
	pow(wall.p[0].y - wall.p[1].y, 2), 0.5);
	walls->dist.y = pow(pow(wall.p[2].x - wall.p[3].x, 2) +
	pow(wall.p[2].y - wall.p[3].y, 2), 0.5);
	walls->maxmindist.x = abs(walls->d1d4.width);
	walls->maxmindist.y = abs(walls->d1d4.start.x);
	walls->shag.y = (float)walls->maxmindist.y / (float)walls->maxmindist.x;
	walls->shag.x = 1.0;
	walls->start = 2;
	if (walls->d1d4.width <= walls->d1d4.start.x)
	{
		walls->maxmindist.x = abs(walls->d1d4.start.x);
		walls->start = 1;
		walls->maxmindist.y = abs(walls->d1d4.width);
		walls->shag.y = 1.0;
		walls->shag.x = (float)walls->maxmindist.y / (float)walls->maxmindist.x;
	}
}

void	setwallskefm(t_drawwallservice *walls, t_tga image, float *offset)
{
	walls->kefm.x = 0;
	walls->kefm.y = ((float)walls->maxmindist.x) / (float)(image.width);
	if (offset[1] < 1)
	{
		walls->kefm.x = 0;
		walls->kefm.y = (((float)walls->maxmindist.x
		/ offset[1])) / (float)(image.width);
	}
	if (offset[0] < 1)
	{
		walls->kefm.x = (float)walls->maxmindist.x
		/ offset[0] - (float)walls->maxmindist.x;
		walls->kefm.y = (((float)walls->maxmindist.x
		/ offset[0])) / (float)(image.width);
	}
	if (offset[1] < 1 && offset[0] < 1)
	{
		walls->kefm.y = (((float)walls->maxmindist.x
		/ (offset[0] * offset[1]))) / (float)(image.width);
		walls->kefm.x = (float)walls->maxmindist.x
		/ (offset[0] * offset[1]) - ((float)walls->maxmindist.x / offset[1]);
	}
}

void	drawwall(uint32_t *p, t_wall wall, t_tga image, float *offset)
{
	t_drawwallservice	walls;
	int					x;

	if (checkwallinwindowarea(wall))
		return ;
	walls.wall = wall;
	setwallsdist(&walls, wall);
	mallocstena(&walls, wall);
	setwallskefm(&walls, image, offset);
	x = 0;
	while (x < walls.maxmindist.x)
	{
		walls.xp = (int)((float)((float)x + walls.kefm.x) / walls.kefm.y);
		brez(walls, x, wall, p);
		x++;
	}
	free(walls.stena[0]);
	free(walls.stena[1]);
	free(walls.stena[2]);
	free(walls.stena[3]);
}
