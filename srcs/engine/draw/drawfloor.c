/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawfloor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 19:10:42 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/04 15:33:31 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	drawfloor(t_doom *doom, t_wall wa, double *offloor, t_wall fl)
{
	float	endy;
	float	y;
	int		x;
	int		i;
	float m;
	float k;
	float xp;
	float yp;
	int startxp;
	int startyp;
	t_fvector2d dir;
	float kef;
	t_rgba	color;
	// printf ("%f\n", player.rotate.z);
	if (wa.p[0].x > wa.p[1].x)
		ft_swap((void**)&wa.p[0], (void**)&wa.p[1]);
	x = wa.p[0].x;
	i = 0;

	dir.x = cos(doom->player.rotate.z);
	dir.y = sin(doom->player.rotate.z);
	while (x < wa.p[1].x)
	{		
		y = flerp(wa.p[0].y, wa.p[1].y, ((float)1 / (wa.p[1].x - wa.p[0].x)) * i);
		endy = 800;
		// m = fl[0].y/offloor[1] / 500;
		// kef = fl[0].y/offloor[1] - fl[0].y;
		while (y < endy)
		{
			//xp = x;
			//yp =(int)((y + kef) / m) ;
			// xp = fl.p[0].x + (x * dir.x) - (fl.p[0].z +xrotate (y * dir.y));
			// yp = fl.p[0].z + (y * dir.y) - (fl.p[0].x + (x * dir.x));
			//fl[1].x задаёт скорость в зависимости ширины сектора
			xp = (int)fabsf(xp) % (int)fl.texture.width;
			yp = (int)fabsf(yp) % (int)fl.texture.height;
			if (yp >= 0 && yp < fl.texture.height && xp >= 0 && xp < fl.texture.width)
			{
				color.red = fl.texture.pic[(int)yp][(int)xp].red;
				color.green = fl.texture.pic[(int)yp][(int)xp].green;
				color.blue = fl.texture.pic[(int)yp][(int)xp].blue;
				//a = image.pic[yp][xp].alpha;
			}
			if (x >= 0 && x < 800 && y >= 0 && y < 800)
				doom->win->pixels[(int)x + ((int)y * 800)] = ((((((255 << 8) | color.red) << 8) |
				color.green) << 8) | color.blue);
			y++;
		}
		i++;
		x++;
	}
}
