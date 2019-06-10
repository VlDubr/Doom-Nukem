/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawceil.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 19:12:43 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/10 14:11:45 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	drawcail(t_doom *doom, t_wall wa, int b)
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
	if (wa.p[b == 3 || b == 5 ? 2 : 0].x > wa.p[b == 3 || b == 5 ? 3 : 1].x)
		ft_swap((void**)&wa.p[b == 3 || b == 5 ? 2 : 0], (void**)&wa.p[b == 3 || b == 5 ? 3 : 1]);
	x = wa.p[b == 5 || b == 5 ? 2 : 0].x;
	i = 0;

	dir.x = cos(doom->player.rotate.z);
	dir.y = sin(doom->player.rotate.z);
	while (x < wa.p[b == 3 || b == 5 ? 3 : 1].x)
	{		
		y = 0;
		endy = flerp(wa.p[b == 3 || b == 5 ? 2 : 0].y, wa.p[b == 3 || b == 5 ? 3 : 1].y, ((float)1 / (wa.p[b == 3 || b == 5 ? 3 : 1].x - wa.p[b == 3 || b == 5 ? 2 : 0].x)) * i);
		// m = fl[0].y/offloor[1] / 500;
		// kef = fl[0].y/offloor[1] - fl[0].y;
		while (y < endy)
		{
			//xp = x;
			//yp =(int)((y + kef) / m) ;
			// xp = fl.p[0].x + (x * dir.x) - (fl.p[0].z +xrotate (y * dir.y));
			// yp = fl.p[0].z + (y * dir.y) - (fl.p[0].x + (x * dir.x));
			//fl[1].x задаёт скорость в зависимости ширины сектора
			xp = (int)fabsf(xp);
			yp = (int)fabsf(yp);
			if (yp >= 0 && yp < wa.texture.height && xp >= 0 && xp < wa.texture.width)
			{
				color.red = wa.texture.pic[(int)yp][(int)xp].red;
				color.green = wa.texture.pic[(int)yp][(int)xp].green;
				color.blue = wa.texture.pic[(int)yp][(int)xp].blue;
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
