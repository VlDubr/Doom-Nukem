/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawwall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmcclure <vmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:52:17 by vmcclure          #+#    #+#             */
/*   Updated: 2019/04/24 20:11:54 by vmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "doom.h"
void brez(float x0, float x1, float y0, float y1, t_tga image,  int xp, int start, uint32_t *p, float	*offset)
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
	float ey;

	e = 1;
	x = x0;
	y = y0;
	dx = fabs(x1 - x0);
	dy = fabs(y1 - y0);
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
			r = image.pic[yp][xp].red;
			g = image.pic[yp][xp].green;
			b = image.pic[yp][xp].blue;
			a = image.pic[yp][xp].alpha;
		}
		if (x >= 0 && x < 800 && y >= 0 && y < 800)
				{
					if (y < y0 && y > y1 && x > 0)
						p[(int)(x -1) + ((int)(y+1) * 800)] = ((((((255 << 8) | r) << 8) | g) << 8) | b);
					p[(int)x + ((int)y * 800)] = ((((((255 << 8) | r) << 8) | g) << 8) | b);

				}
		// SDL_SetRenderDrawColor(renderer, r, g, b, 255);
		// 	SDL_RenderDrawPoint (renderer,x, y);
	}
}
void drow_wall(uint32_t *p, t_wall wall, t_tga image, float	*offset)
{
	int dx1;
	int dy1;
	int dx4;
	int dy4;
	int dist1;
	int dist2;
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
	int start;

	// if (wall.p[2].x > wall.p[3].x && wall.p[0].x > wall.p[1].x)
	// {
	// 	ft_swap((void**)&wall.p[0], (void**)&wall.p[1]);
	// 	ft_swap((void**)&wall.p[2], (void**)&wall.p[3]);
	// 	printf ("x0 %f y0 %f \n", wall.p[0].x, wall.p[0].y);
	// }
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
	dx1 = (wall.p[1].x - wall.p[0].x);
	dy1 = (wall.p[1].y - wall.p[0].y);
	dx4 = (wall.p[3].x - wall.p[2].x);
	dy4 = (wall.p[3].y - wall.p[2].y);
	dist1 = pow(pow(wall.p[0].x - wall.p[1].x, 2) + pow(wall.p[0].y - wall.p[1].y, 2), 0.5);
	dist2 = pow(pow(wall.p[2].x - wall.p[3].x, 2) + pow(wall.p[2].y- wall.p[3].y, 2), 0.5);
	if (dx4 > dx1)
	{
		maxdist = abs(dx4);
		start = 2;
		mindist = abs(dx1);
		shag_dlya_1_steni = (float)mindist / (float)maxdist;
		shag_dlya_2_steni = 1.0;
	}
	else
	{
		maxdist = abs(dx1);
		start = 1;
		mindist = abs(dx4);
		shag_dlya_1_steni = 1.0;
		shag_dlya_2_steni = (float)mindist / (float)maxdist;
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
		stena1_x[i] = wall.p[0].x + (i * shag_dlya_1_steni);
		stena1_y[i] = wall.p[0].y + (i * shag_dlya_1_steni * ((float)dist1/(float)dx1)) * sin(dir1);
		stena2_x[i] = wall.p[2].x + (i * shag_dlya_2_steni);
		stena2_y[i] = wall.p[2].y + (i * shag_dlya_2_steni * ((float)dist2/(float)dx4)) *sin(dir4);
		ugol_sten[i] = atan((float)(stena2_y[i] - stena1_y[i])/(stena2_x[i] - stena1_x[i]));
		dist_sten[i] = sqrt(pow(stena2_x[i] - stena1_x[i], 2) + pow(stena2_y[i] - stena1_y[i], 2));
		if (ugol_sten[i] > 0)
			ugol_sten[i] -= M_PI;
		i++;
	}
	// m = maxdist / (float)(image.width);
	x = 0;
	float kef;
	kef = 0;
	m = ((float)maxdist) / (float)(image.width);
	if (wall.p[0].x < 0)
	{
		kef = (float)maxdist/offset[0] - (float)maxdist;
		m = ((float)maxdist/offset[0]) / (float)(image.width);
			//  printf ("%f\n", offset[0]);
	}
	// if (wall.p[1].x > 800)
	// {
	// 	return ;
	// 	kef = -((float)maxdist/offset[1] - maxdist);
	// 	m = ((float)maxdist/offset[1]) / (float)(image.width);

	// }



	while (x < maxdist)
	{
		y = 0;
		xp = (int)((float)(x+kef)/m);
		brez (stena1_x[x], stena2_x[x], stena1_y[x], stena2_y[x], image, xp,  start, p, offset);
		// while (y < dist_sten[x] *2)
		// {
		// 	k = dist_sten[x] *2   / (image.height -1 );
		// 	m = (float)maxdist / (image.width -1);
		// 	x0 = (stena1_x[x]) + y * 0.5  * cos(ugol_sten[x]);
		// 	y0 = (stena1_y[x]) + y * 0.5 * sin(ugol_sten[x]);
		// 	yp = (int)(y/k);
		// 	xp = (int)(x/m);
		// 	r = image.pic[yp][xp].red;
		// 	g = image.pic[yp][xp].green;
		// 	b = image.pic[yp][xp].blue;
		// 	a = image.pic[yp][xp].alpha;
		// 	// SDL_SetRenderDrawColor(renderer, r, g, b, 255);
		// 	// SDL_RenderDrawPoint (renderer,x0, y0);
		// 	if (x0 >= 0 && x0 < 800 && y0 >= 0 && y0 < 600)
		// 		p[(int)x0 + (y0 * 800)] = ((((((255 << 8) | r) << 8) | g) << 8) | b);
		// 	y++;
		// }
		x++;
	}
	i = 0;
	// SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	// while (i < maxdist)
	// {
	// 	SDL_RenderDrawPoint (renderer,stena1_x[i], stena1_y[i]);
	// 	i++;
	// }
	// SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	// SDL_RenderDrawPoint (renderer,wall.p[0].x, wall.p[0].y);
	// SDL_RenderDrawPoint (renderer,wall.p[1].x, wall.p[1].y);
	// SDL_RenderDrawPoint (renderer,wall.p[2].x, wall.p[2].y);
	// SDL_RenderDrawPoint (renderer,wall.p[3].x, wall.p[3].y);
	free(stena1_x);
	free(stena1_y);
	free(stena2_x);
	free(stena2_y);
	free(ugol_sten);
	free(dist_sten);
}
