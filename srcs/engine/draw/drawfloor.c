#include "doom.h"

void	drawfloor(uint32_t *p, t_wall wa, t_rgb color, t_player player, double *offloor)
{
	float	endy;
	float	y;
	int		x;
	int		i;
	float m;
	float k;
	int xp;
	int yp;
	int startxp;
	int startyp;

	t_fvector2d dir;
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
		while (y < endy)
		{
			xp = (int)((((y-800) * dir.y) +  (dir.x * (x-400))) - (1300.0 * offloor[1])) % (int)tgafloor->width;
			yp = (int)((((x-400) * dir.y) -  (dir.x * (y-800))) - (1300.0 * offloor[0])) % (int)tgafloor->height;
			xp = abs(xp);
			yp = abs(yp);
			if (yp >= 0 && yp < tgafloor->height && xp >= 0 && xp < tgafloor->width)
			{
				color.red = tgafloor->pic[yp][xp].red;
				color.green = tgafloor->pic[yp][xp].green;
				color.blue = tgafloor->pic[yp][xp].blue;
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
