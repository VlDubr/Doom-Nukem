/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawwall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:52:17 by vmcclure          #+#    #+#             */
/*   Updated: 2019/06/12 19:10:31 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "doom.h"
void brez(float x0, float x1, float y0, float y1, t_tga image,  int xp, int start, uint32_t *p, float	*offset, float light)
{
	float dx;
	float dy;
	float x;
	float y;
	float d;
	float d1;
	float d2;
	t_rgba	color;
	int r;
	int g;
	int b;
	int yp;
	float k;
	float e;
	char a;
	float ey;
	float dir;
	e = 1;
	x = x0;
	y = y0;
	dx = fabs(x1 - x0);
	dy = fabs(y1 - y0);
	d = 2* (dx - dy);
	d1 = 2 * dx;
	d2 = (dx - dy) *2.0;
	ey = -1;
	if (x1 < x0)
	 	e = -1;
	if (start == 2)
		{
			y = y1;
			x = x1;
			ey = 1;
		}
	if (ey == 1)
		e *=-1;
	k = dy   / (image.height);
	while (y <= y0 && y >= y1)
	{
		if ((start == 2 && y >= 800) || (start == 1 && y < 0))
            break ;
		if ((start == 1 && y >= 800))
			y = 800;		
		if ((start == 2 && y < 0))
			y = 0;
		y += ey; ;
		if (d < 0)
			d +=d1;
		else
		{
			x += e;
			d +=d2;
		}
		yp =(int)((y - y1)/k);
		if (yp >= 0 && yp < image.height && xp >= 0 && xp < image.width)
		{
			color = image.pic[yp][xp];
		}
		if (x >= 0 && x < 800 && y >= 0 && y < 800)
		{
			t_rgba		pc;
			t_rgba		newc;
			uint32_t	c;
			int l = light == 1 ? 2 : 1;

			c = p[(int)x + (((int)y) * 800)];
			pc.alpha = c >> 24;
			pc.red = (((c << 8) >> 24));
			pc.green = (((c << 16) >> 24));
			pc.blue = (((c << 24) >> 24));
			if (color.alpha == 255)
			{
				if (x >= 0 && x < 800 && y >= 0 && y < 800)
					p[(int)x + (((int)y) * 800)] = ((((((color.alpha << 8) | color.red / l) << 8) |
					color.green / l) << 8) | color.blue / l);;
			}
			else if (color.alpha < 255 && color.alpha > 0)
			{
				newc = opacityrgba(pc, color);
				p[(int)x + (((int)y) * 800)] = ((((((newc.alpha << 8) | newc.red / l) << 8)
				| newc.green / l) << 8) | newc.blue / l);
			}
		}
	}
}

void	initmmdshagstart(t_ivector2d *maxmindist, t_fvector2d *shag,
int *start, t_irect d1d4)
{
	maxmindist->x = abs(d1d4.width);
	maxmindist->y = abs(d1d4.start.x);
	shag->y = (float)maxmindist->y / (float)maxmindist->x;
	shag->x = 1.0;
	*start = 2;
	if (d1d4.width <= d1d4.start.x)
	{
		maxmindist->x = abs(d1d4.start.x);
		start = 1;
		maxmindist->y = abs(d1d4.width);
		shag->y = 1.0;
		shag->x = (float)maxmindist->y / (float)maxmindist->x;
	}
}

void	mallocstena(float *stena[4], t_ivector2d maxmindist)
{
	stena[0] = (float *)malloc((sizeof(float)) * (maxmindist.x + 1));
	stena[1] = (float *)malloc((sizeof(float)) * (maxmindist.x + 1));
	stena[2] = (float *)malloc((sizeof(float)) * (maxmindist.x + 1));
	stena[3] = (float *)malloc((sizeof(float)) * (maxmindist.x + 1));
}

void drawwall(uint32_t *p, t_wall wall, t_tga image, float	*offset)
{
	t_irect	d1d4;
	t_ivector2d dist;
	t_ivector2d	xy;
	float kef;
	float m;
	float *stena[4];
	t_fvector2d	shag;
	t_ivector2d maxmindist;
	int start;
	if( wall.p[0].x > 810 || wall.p[1].x > 810 || wall.p[0].x < -2 || wall.p[1].x < -2)
		return ;
	d1d4 = setirect(setivector2d((wall.p[1].x - wall.p[0].x), (wall.p[1].y - wall.p[0].y)), (wall.p[3].x - wall.p[2].x), (wall.p[3].y - wall.p[2].y));
	dist.x = pow(pow(wall.p[0].x - wall.p[1].x, 2) + pow(wall.p[0].y - wall.p[1].y, 2), 0.5);
	dist.y = pow(pow(wall.p[2].x - wall.p[3].x, 2) + pow(wall.p[2].y- wall.p[3].y, 2), 0.5);

	initmmdshagstart(&maxmindist, &shag, &start, d1d4);
	mallocstena(stena, maxmindist);
	xy.y = 0;
	while (xy.y < maxmindist.x)
	{
		stena[0][xy.y] = wall.p[0].x + (xy.y * shag.y);
		stena[1][xy.y] = wall.p[0].y + (xy.y * shag.y * ((float)dist.x / (float)d1d4.start.x)) * sin(atan((float)d1d4.start.y / (float)d1d4.start.x));
		stena[2][xy.y] = wall.p[2].x + (xy.y * shag.x);
		stena[3][xy.y] = wall.p[2].y + (xy.y * shag.x * ((float)dist.y / (float)d1d4.width)) * sin(atan((float)d1d4.height / (float)d1d4.width));
		xy.y++;
	}

	kef = 0;
	m = ((float)maxmindist.x) / (float)(image.width);

	if (offset[1] < 1)
	{
		kef = 0;
		m = (((float)maxmindist.x / offset[1])) / (float)(image.width);
	}
	if (offset[0] < 1)
	{
		kef = (float)maxmindist.x / offset[0] - (float)maxmindist.x;
		m = (((float)maxmindist.x / offset[0])) / (float)(image.width);
	}
	if (offset[1] < 1 && offset[0] < 1)
	{
		m = (((float)maxmindist.x / (offset[0] * offset[1]))) / (float)(image.width);
		kef = (float)maxmindist.x / (offset[0]* offset[1]) - ((float)maxmindist.x / offset[1]);
	}
	xy.x = 0;
	while (xy.x < maxmindist.x)
	{
		brez (stena[0][xy.x], stena[2][xy.x], stena[1][xy.x], stena[3][xy.x], image,
		(int)((float)((float)xy.x + kef) / m),  start, p, offset, wall.light);
		xy.x++;
	}
	free(stena[0]);
	free(stena[1]);
	free(stena[2]);
	free(stena[3]);
}
