#include "doom.h"

void	drawfloor(uint32_t *p, t_wall wa, t_rgb color, t_player player, double *offloor)
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
	// printf ("%f\n", player.rotate.z);
	if (wa.p[0].x > wa.p[1].x)
		ft_swap((void**)&wa.p[0], (void**)&wa.p[1]);
	x = wa.p[0].x;
	i = 0;
<<<<<<< HEAD
	dir.x = cos (-player.rotate.z);
=======
	m = ((float)1000) / (float)(tgafloor->width);
	y = flerp(wa.p[0].y, wa.p[1].y, ((float)1 / (wa.p[1].x - wa.p[0].x)) * i);
	dir.x = cos(-player.rotate.z);
>>>>>>> fed40e7414f0038dde6cbca73a9c754a5d16b445
	dir.y = sin(-player.rotate.z);
	while (x < wa.p[1].x)
	{		
		y = flerp(wa.p[0].y, wa.p[1].y, ((float)1 / (wa.p[1].x - wa.p[0].x)) * i);
		endy = 800;
		while (y < endy)
		{
<<<<<<< HEAD
			xp = (int)((((y-800) * dir.y) +  (dir.x * (x-400))) - (1300.0 * offloor[1])) % (int)tgafloor->width;
			yp = (int)((((x-400) * dir.y) -  (dir.x * (y-800))) - (1300.0 * offloor[0])) % (int)tgafloor->height;
			xp = abs(xp);
			yp = abs(yp);
=======
			xp = (int)(((float)y * dir.y) +  (dir.x * (float)x)) % (int)tgafloor->width;
			yp = (int)(((float)x * dir.y) -  (dir.x * (float)y)) % (int)tgafloor->height;
			xp = fabsf(xp);
			yp = fabsf(yp);
>>>>>>> fed40e7414f0038dde6cbca73a9c754a5d16b445
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
