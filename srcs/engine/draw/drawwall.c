/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawwall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmcclure <vmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:52:17 by vmcclure          #+#    #+#             */
/*   Updated: 2019/04/18 16:17:40 by vmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "doom.h"
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
	char a;
	float *stena1_x;
	float *stena1_y;
	float *stena2_x;
	float *stena2_y;

	float *dist_sten;
	float *ugol_sten;
	float shag_dlya_2_steni;
	float shag_dlya_1_steni;
	int maxdist;
	int x0;
	int y0;
	int x2;
	int y2;
	int x1;
	int y1;
	int xp;
	int yp;
	int mindist;
	int buf;

	if (wall.p[2].x > wall.p[3].x)
	{
		buf = wall.p[2].x;
		wall.p[2].x = wall.p[3].x;
		wall.p[2].x = buf;
	}
	if (wall.p[0].x > wall.p[1].x)
	{
		buf = wall.p[0].x;
		wall.p[0].x = wall.p[1].x;
		wall.p[1].x = buf;
	}
	dx1 = (wall.p[0].x - wall.p[1].x);
	dy1 = (wall.p[0].y - wall.p[1].y);
	dx4 = (wall.p[2].x - wall.p[3].x);
	dy4 = (wall.p[2].y - wall.p[3].y);
	dist1 = pow(pow(wall.p[0].x - wall.p[1].x, 2) + pow(wall.p[0].y - wall.p[1].y, 2), 0.5);
	dist4 = pow(pow(wall.p[2].x - wall.p[3].x, 2) + pow(wall.p[2].y- wall.p[3].y, 2), 0.5);
	if (dist4 > dist1)
	{
		maxdist = dist4;
		mindist = dist1;
		shag_dlya_1_steni = 1;
		shag_dlya_2_steni = (float)mindist / (float)maxdist;
	}
	else
	{
		maxdist = dist1;
		mindist = dist4;
		shag_dlya_1_steni = (float)mindist / (float)maxdist;
		shag_dlya_2_steni = 1;
	}

	dir1 = (atan((float)dy1/(float)dx1));
	dir4 = (atan((float)dy4/(float)dx4));
	stena1_x = (float *)malloc((sizeof(float)) * (maxdist+1));
	stena1_y = (float *)malloc((sizeof(float)) * (maxdist+1));
	stena2_x = (float *)malloc((sizeof(float)) * (maxdist+1));
	stena2_y = (float *)malloc((sizeof(float)) * (maxdist+1));
	ugol_sten = (float *)malloc((sizeof(float)) * (maxdist+1));
	dist_sten = (float *)malloc((sizeof(float)) * (maxdist+1));
	i = 0;
	while (i < maxdist)
	{
		stena1_x[i] = wall.p[2].x + (i * shag_dlya_1_steni) * cos(dir4);
		stena1_y[i] = wall.p[2].y + (i * shag_dlya_1_steni) * sin(dir4);
		stena2_x[i] = wall.p[0].x + (i * shag_dlya_2_steni) * cos(dir1);
		stena2_y[i] = wall.p[0].y + (i * shag_dlya_2_steni) * sin(dir1);
		ugol_sten[i] = atan((float)(stena1_y[i] - stena2_y[i])/(stena1_x[i] - stena2_x[i]));

		dist_sten[i] = sqrt(pow(stena2_x[i] - stena1_x[i], 2) + pow(stena2_y[i] - stena1_y[i], 2));
		 printf ("%f\n", dist_sten[i]);
		if (ugol_sten[i] > 0)
			ugol_sten[i] -= M_PI;
		i++;
	}

	x = 0;
	while (x < maxdist)
	{
		y = 0;
		while (y < dist_sten[x] )
		{
			k = dist_sten[x]   / image.height;
			m = (float)maxdist / image.width;
			x0 = (stena1_x[x]) + y * 1  * cos(ugol_sten[x]);
			y0 = (stena1_y[x]) + y * 1 * sin(ugol_sten[x]);
			yp = (int)(y/k);
			xp = (int)(x/m);
			r = image.pic[yp][xp].red;
			g = image.pic[yp][xp].green;
			b = image.pic[yp][xp].blue;
			a = image.pic[yp][xp].alpha;
			if (x0 >= 0 && x0 < 800 && y0 >= 0 && y0 < 600)
				p[(int)x0 + (y0 * 800)] = ((((((255 << 8) | r) << 8) | g) << 8) | b);
			y++;
		}
		x++;
	}
	free(stena1_x);
	free(stena1_y);
	free(stena2_x);
	free(stena2_y);
	free(ugol_sten);
	free(dist_sten);
}