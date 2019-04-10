#include "doom.h"

void		drawlinelow(uint32_t *p, t_fvector start, t_fvector end, t_rgb color)
{
	t_fvector		delta;
	t_fvector		edi;
	t_ivector2d		cord;

	delta = setfvector(fabs(start.x - end.x),
	fabs(start.y - end.y), fabs(start.y - end.y));
	edi.x = 0;
	edi.y = end.y - start.y;
	edi.y > 0 ? edi.y = 1 : 0;
	edi.y < 0 ? edi.y = -1 : 0;
	cord = setivector2d(start.x, start.y);
	edi.z = 0;
	while (edi.z < end.x - start.x)
	{
		if (cord.x + edi.z >= 0 && cord.x + edi.z < 800 && cord.y >= 0 && cord.y < 600)
			p[(int)(cord.x + edi.z) + (cord.y * 800)] = ((((((255 << 8) |
			color.red) << 8) | color.green) << 8) | color.blue);
		edi.x = edi.x + delta.z;
		if (2 * edi.x >= delta.x)
		{
			cord.y = cord.y + edi.y;
			edi.x = edi.x - delta.x;
		}
		edi.z++;
	}
}

void		drawlinehight(uint32_t *p, t_fvector start, t_fvector end, t_rgb color)
{
	t_fvector		delta;
	t_fvector		edi;
	t_ivector2d		cord;

	delta = setfvector(fabs(start.x - end.x),
	fabs(start.y - end.y), fabs(start.x - end.x));
	edi.x = 0;
	edi.y = end.x - start.x;
	edi.y > 0 ? edi.y = 1 : 0;
	edi.y < 0 ? edi.y = -1 : 0;
	cord = setivector2d(start.x, start.y);
	edi.z = 0;
	while (edi.z < end.y - start.y)
	{
		if (cord.x >= 0 && cord.x < 800 && cord.y + edi.z >= 0 && cord.y + edi.z < 600)
			p[cord.x + (int)((cord.y + edi.z) * 800)] = ((((((255 << 8) |
			color.red) << 8) | color.green) << 8) | color.blue);
		edi.x = edi.x + delta.z;
		if (2 * edi.x >= delta.y)
		{
			cord.x = cord.x + edi.y;
			edi.x = edi.x - delta.y;
		}
		edi.z++;
	}
}

void		drawline(uint32_t *p, t_fvector start, t_fvector end, t_rgb color)
{
	if (fabs(end.y - start.y) < fabs(end.x - start.x))
	{
		if (start.x > end.x)
			drawlinelow(p, end, start, color);
		else
			drawlinelow(p, start, end, color);
	}
	else
	{
		if (start.y > end.y)
			drawlinehight(p, end, start, color);
		else
			drawlinehight(p, start, end, color);
	}
}
