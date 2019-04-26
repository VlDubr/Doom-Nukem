/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collide.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmcclure <vmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 18:40:19 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/25 20:46:00 by vmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

t_line			setline(t_fvector2d a1, t_fvector2d a2,
t_fvector2d b1, t_fvector2d b2)
{
	t_line l;

	l.p[0] = a1;
	l.p[1] = a2;
	l.p[2] = b1;
	l.p[3] = b2;
	return (l);
}

float	area(t_fvector2d a, t_fvector2d b, t_fvector2d c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int	collideline1(float a, float b, float c, float d)
{
	float tmp;

	if (a > b)
	{
		tmp = a;
		a = b;
		b = tmp;
	}
	if (c > d)
	{
		tmp = c;
		c = d;
		d = tmp;
	}
	return (ft_fmax(a, c) <= ft_fmin(b, d));
}

int	collideline(t_line line)
{
	if (collideline1(line.p[0].x, line.p[1].x, line.p[2].x, line.p[3].x))
		if (collideline1(line.p[0].y, line.p[1].y, line.p[2].y, line.p[3].y))
			if (area(line.p[0], line.p[1], line.p[2]) * area(line.p[0], line.p[1], line.p[3]) <= 0)
				if (area(line.p[2], line.p[3], line.p[0]) * area(line.p[2], line.p[3], line.p[1]) <= 0)
					return (1);
	return (0);
}

int		collide(t_fvector2d pos, t_fvector2d newpos, t_fvector *w, size_t count)
{
	t_fvector2d	p1;
	t_fvector2d	p2;
	size_t		c;

	c = 0;
	while (c < count)
	{
		p1 = setfvector2d(w[c].x, w[c].y);
		p2 = setfvector2d(w[c + 1 >= count ? 0 : c + 1].x,
		w[c + 1 >= count ? 0 : c + 1].y);
		if (w[c].z == -1)
			if (collideline(setline(pos,
			newpos, p1, p2)))
				return (1);
		c++;
	}
	return (0);
}
