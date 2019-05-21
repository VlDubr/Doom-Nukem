#include "doom.h"

void	drawfloor(uint32_t *p, t_wall wa, t_rgb color, t_player player)
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
	k = 1000.0   / (tgafloor->height);
	x = wa.p[0].x;
	i = 0;
	m = ((float)1000) / (float)(tgafloor->width);
	y = flerp(wa.p[0].y, wa.p[1].y, ((float)1 / (wa.p[1].x - wa.p[0].x)) * i);
	startxp = (int)((400.0)/m)  ;
	startyp = (int)(400.0)/k;
	dir.x = cos (player.rotate.z);
	dir.y = sin(player.rotate.z);
	while (x < wa.p[1].x)
	{
		//xp = (int)((float)((float)x)/m);//  + (int)player.pos.z*19;; //* cos (player.rotate.z) 
		y = flerp(wa.p[0].y, wa.p[1].y, ((float)1 / (wa.p[1].x - wa.p[0].x)) * i);
		endy = 800;
		while (y < endy)
		{
			xp = (int)(((float)y * dir.y) +  (dir.x * (float)x)) % (int)tgafloor->width;
			//yp = (int)(y)/k;// - (int)player.pos.x*10 ;  // * sin (player.rotate.z) 
			yp = (int)(((float)x * dir.y) +  (dir.x * (float)y)) % (int)tgafloor->height;
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
