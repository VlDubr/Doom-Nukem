/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawwall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmcclure <vmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:52:17 by vmcclure          #+#    #+#             */
/*   Updated: 2019/04/18 16:55:19 by vmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "doom.h"

void brez(float x0, float x1, float y0, float y1, t_tga image,  int xp, float stena, uint32_t *p)
{
	float dx;
	float dy;
	float x;
	float y;
	float d;
	float d1;
	float d2;
	int r;
	int g;
	int b;
	int yp;
	float k;
	float e;
	char a;

	e = 1;
	x = x0;
	y = y0;
	dx = fabs(x1 - x0);
	if (stena == 1)
		{
			e = -1;
			y = y1;
			x = x1;
		}		
	dy = fabs(y1 - y0);
	d = 2* (dx - dy);
	d1 = 2 * dx * e;
	d2 = (dx - dy) *2.0;

	k = dy   / (image.height);

	while (y >= y0 && y <= y1)
	{
		y += e ;
		if (d < 0)
			d +=d1* e;
		else
		{
			x += 1;
			d +=d2;
		}
		yp =(int)((y - (y0) )/k);
		if (yp > 0 && yp < image.height && xp > 0 && xp < image.width)
		{
			r = image.pic[yp][xp].red;
			g = image.pic[yp][xp].green;
			b = image.pic[yp][xp].blue;
			a = image.pic[yp][xp].alpha;
		}
		// else 
		// 	{
		// 		r = 255;
		// 		g = 0;
		// 		b = 0;
				
		// 	}
		if (x >= 0 && x < 800 && y >= 0 && y < 600)
				{	
					
					p[(int)x + ((int)y * 800)] = ((((((255 << 8) | r) << 8) | g) << 8) | b);
				}
	}
	
}
void drow_wall(uint32_t *p, t_wall wall, t_tga image)
{
	int dx1;
	int dy1;
	int dx4;
	int dy4;
	int dist1;
	int dist4;
	float dir1;
	float dir4;
	float k;
	char r;
	char g;
	char b;
	int i;
	int x;
	int y;
	float m;
	float *stena1_x;
	float *stena1_y;
	float *stena2_x;
	float *stena2_y;
	float shag_dlya_2_steni;
	float shag_dlya_1_steni;
	int maxdist;
	int x0;
	int y0;
	int x1;
	int y1;
	int xp;
	int yp;
	int mindist;
	int buf;
	// if (wall.p[2].x > wall.p[3].x)
	// {
	// 	buf = wall.p[2].x;
	// 	wall.p[2].x = wall.p[3].x;
	// 	wall.p[2].x = buf;
	// }
	// if (wall.p[0].x > wall.p[1].x)
	// {
	// 	buf = wall.p[0].x;
	// 	wall.p[0].x = wall.p[1].x;
	// 	wall.p[1].x = buf;
	// }
	dx1 = (wall.p[0].x - wall.p[1].x);
	dy1 = (wall.p[0].y - wall.p[1].y);
	dx4 = (wall.p[2].x - wall.p[3].x);
	dy4 = (wall.p[2].y - wall.p[3].y);


	// clock_t start = clock();
	dist1 = pow(pow(wall.p[0].x - wall.p[1].x, 2) + pow(wall.p[0].y - wall.p[1].y, 2), 0.5);
	dist4 = pow(pow(wall.p[2].x - wall.p[3].x, 2) + pow(wall.p[2].y- wall.p[3].y, 2), 0.5);
	if (dx4 < dx1)
	{
		maxdist = fabs(wall.p[1].x - wall.p[0].x);
		mindist = fabs(wall.p[3].x - wall.p[2].x);
		shag_dlya_1_steni = (float)mindist / (float)maxdist;
		k = 2;
		shag_dlya_2_steni = 1;		
	}
	else
	{
		maxdist =fabs(wall.p[3].x - wall.p[2].x);
		mindist =fabs(wall.p[1].x - wall.p[0].x);
		shag_dlya_1_steni = 1;
		shag_dlya_2_steni = (float)mindist / (float)maxdist;
		k = 1;
	}	
	dir1 = (atan((float)dy1/(float)dx1));
	dir4 = (atan((float)dy4/(float)dx4));
	// printf ("%f\n", dir4);
	// if (dir1 < 0)
	// 	 	dir1 -= M_PI;
	// if (dir4 < 0)
	// 	dir4 -= M_PI;
	stena1_x = (float *)malloc((sizeof(float)) * (maxdist+1));
	stena1_y = (float *)malloc((sizeof(float)) * (maxdist+1));
	stena2_x = (float *)malloc((sizeof(float)) * (maxdist+1));
	stena2_y = (float *)malloc((sizeof(float)) * (maxdist+1));

	i = 0;
	while (i <= maxdist)
	{
			stena1_x[i] = wall.p[0].x + (i * shag_dlya_2_steni);
			stena1_y[i] = wall.p[0].y + (i * shag_dlya_2_steni * (dist1/(float)dx1)) * sin(dir4);
			stena2_x[i] = wall.p[2].x + (i * shag_dlya_1_steni);
			stena2_y[i] = wall.p[2].y + (i * shag_dlya_1_steni * (dist4/(float)dx4)) * sin(dir1);
		i++;
	}
	x = 0;
	m = maxdist / (float)(image.width);
	while (x < maxdist)
	{
		xp = (int)((x)/m);
		brez (stena1_x[x], stena2_x[x], stena1_y[x], stena2_y[x], image, xp, k, p);
		x++;
	}
	// clock_t end = clock();
	// double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	// printf("The time: %f seconds\n", seconds);
	free(stena1_x);
	free(stena1_y);
	free(stena2_x);
	free(stena2_y);
}
