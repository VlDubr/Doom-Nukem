#include "doom.h"

void	drawceil(uint32_t *p, t_wall wa, t_rgb color)
{
	float	endy;
	float	y;
	int		x;
	int		i;

	if (wa.p[2].x > wa.p[3].x)
		ft_swap((void**)&wa.p[2], (void**)&wa.p[3]);

	x = wa.p[2].x;
	i = 0;
	while (x < wa.p[3].x)
	{
		y = 0;
		endy = flerp(wa.p[2].y, wa.p[3].y, ((float)1 / (wa.p[3].x - wa.p[2].x)) * i);
		while (y < endy)
		{
			if (x >= 0 && x < 800 && y >= 0 && y < 600)
				p[(int)x + ((int)y * 800)] = ((((((255 << 8) | color.red) << 8) |
				color.green) << 8) | color.blue);
			y++;
		}
		i++;
		x++;
	}
}
