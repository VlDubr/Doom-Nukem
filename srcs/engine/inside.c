/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inside.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:47:14 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/11 19:27:29 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	inside(t_fvector2d i, t_fvector *p, size_t size)
{
	int			b;
	t_ivector	c;
	t_ivector2d	S;
	t_ivector2d	S2;

	c.x = 0;
	while (c.x < size)
	{
		b = 0;
		c.y = c.x < size - 1 ? c.x + 1 : 0;
		while (b == 0)
		{
			c.z = c.y + 1;
			if (c.z >= size)
				c.z = 0;
			if (c.z == (c.x < size - 1 ? c.x + 1 : 0))
				break ;
			S.x = fabsf(p[c.y].x * (p[c.z].y - p[c.x].y) +
					  p[c.z].x * (p[c.x].y - p[c.y].y) +
					  p[c.x].x * (p[c.y].y - p[c.z].y));
			S.y = fabsf(p[c.y].x * (p[c.z].y - i.y) +
					  p[c.z].x *      (i.y - p[c.y].y) +
					  i.x *      (p[c.y].y - p[c.z].y));
			S2.x = fabsf(p[c.x].x *(p[c.z].y - i.y) +
					   p[c.z].x *     (i.y - p[c.x].y) +
					   i.x *     (p[c.x].y - p[c.z].y));
			S2.y = fabsf(p[c.y].x *(p[c.x].y - i.y) +
					   p[c.x].x *     (i.y - p[c.y].y) +
					   i.x *     (p[c.y].y - p[c.x].y));
			if (S.x == S.y + S2.x + S2.y)
			{
				b = 1;
				break ;
			}
			c.y++;
			if (c.y >= size)
				c.y = 0;
		}
		if (b == 0)
			break ;
		c.x++;
	}
	return (b);
}
