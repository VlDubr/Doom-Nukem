/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collide.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 18:40:19 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/11 18:37:20 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

t_line			setline(t_fvector2d a1, t_fvector2d a2,
t_fvector2d b1, t_fvector2d b2)
{
	t_line l;

	l.a1 = a1;
	l.a2 = a2;
	l.b1 = b1;
	l.b2 = b2;
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
	if (collideline1(line.a1.x, line.a2.x, line.b1.x, line.b2.x))
		if (collideline1(line.a1.y, line.a2.y, line.b1.y, line.b2.y))
			if (area(line.a1, line.a2, line.b1) * area(line.a1, line.a2, line.b2) <= 0)
				if (area(line.b1, line.b2, line.a1) * area(line.b1, line.b2, line.a2) <= 0)
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
