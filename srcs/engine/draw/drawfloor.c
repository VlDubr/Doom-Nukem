#include "doom.h"

void	drawfloor(uint32_t *p, t_wall wa, t_rgb color, t_player player, double *offloor, t_fvector	*fl)
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
	// printf ("%f\n", player.rotate.z);
	if (wa.p[0].x > wa.p[1].x)
		ft_swap((void**)&wa.p[0], (void**)&wa.p[1]);
	x = wa.p[0].x;
	i = 0;
	dir.x = cos (-player.rotate.z);
	dir.y = sin(-player.rotate.z);

	while (x < wa.p[1].x)
	{		
		y = flerp(wa.p[0].y, wa.p[1].y, ((float)1 / (wa.p[1].x - wa.p[0].x)) * i);
		endy = 800;
		m = fl[0].y/offloor[1] / 500;
		kef = fl[0].y/offloor[1] - fl[0].y;
		while (y < endy)
		{
			xp = x;
			yp =(int)((y + kef) / m) ;
			
			// xp = (int)((((y - fl[0].y) * dir.y) +  (dir.x * (x -400)))) % (int)tgafloor->width;
			// yp = (int)((((x -400) * dir.y) -  (dir.x * (y  - fl[0].y )))) % (int)tgafloor->height;
			// fl[1].x задаёт скорость в зависимости ширины сектора
			xp = (int)fabsf(xp)% (int)tgafloor->width;
			yp = (int)fabs(yp) % (int)tgafloor->height;
			if (yp >= 0 && yp < tgafloor->height && xp >= 0 && xp < tgafloor->width)
			{
				color.red = tgafloor->pic[(int)yp][(int)xp].red;
				color.green = tgafloor->pic[(int)yp][(int)xp].green;
				color.blue = tgafloor->pic[(int)yp][(int)xp].blue;
				//a = image.pic[yp][xp].alpha;
			}
			if (x >= 0 && x < 800 && y >= 0 && y < 800)
				p[(int)x + ((int)y * 800)] = ((((((255 << 8) | color.red) << 8) |
				color.green) << 8) | color.blue);
			y++;
		}
		i++;
		x++;
	}
}
