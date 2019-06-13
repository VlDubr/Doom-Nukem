/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 17:00:53 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/13 18:02:45 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		crossline(t_line line, t_fvector2d *ret)
{
	float dx1;
	float dy1;
	float dx2;
	float dy2;

	dx1 = line.p[1].x - line.p[0].x;
	dy1 = line.p[1].y - line.p[0].y;
	dx2 = line.p[3].x - line.p[2].x;
	dy2 = line.p[3].y - line.p[2].y;
	ret->x = dy1 * dx2 - dy2 * dx1;
	if (!ret->x || !dx2)
		return (0);
	ret->y = line.p[2].x * line.p[3].y - line.p[2].y * line.p[3].x;
	ret->x = ((line.p[0].x * line.p[1].y - line.p[0].y
	* line.p[1].x) * dx2 - ret->y * dx1) / ret->x;
	ret->y = (dy2 * ret->x - ret->y) / dx2;
	return (((line.p[0].x <= ret->x && line.p[1].x >= ret->x) ||
	(line.p[1].x <= ret->x && line.p[0].x >= ret->x))
	&& ((line.p[2].x <= ret->x && line.p[3].x >= ret->x)
	|| (line.p[3].x <= ret->x && line.p[2].x >= ret->x)));
}

int		switchcordwall(t_fvector *p1, t_fvector *p2, float *offset,
t_fvector2d angle)
{
	float		t1;
	float		t2;
	t_fvector2d	ret;
	t_fvector	tmpp;
	t_line		l;

	t1 = sqrt((fabs(p2->x - p1->x) * fabs(p2->x - p1->x)) +
	(fabs(p2->z - p1->z) * fabs(p2->z - p1->z)));
	l = setline(setfvector2d(p1->x, p1->z), setfvector2d(p2->x, p2->z),
	setfvector2d(0, 0), setfvector2d(angle.x * 100, angle.y * 100));
	crossline(l, &ret);
	tmpp = *p1;
	p1->x = ret.x;
	p1->z = ret.y;
	t2 = sqrt((fabs(p2->x - p1->x) * fabs(p2->x - p1->x))
	+ (fabs(p2->z - p1->z) * fabs(p2->z - p1->z)));
	*offset = t2 / t1;
	p1->y = flerp(tmpp.y, p2->y, 1 - (*offset));
	p1->w = flerp(tmpp.w, p2->w, 1 - (*offset));
	return (1);
}

void	leftclip(t_fvector p[4], float offset[4])
{
	switchcordwall(&p[0], &p[1], &offset[0], setfvector2d(
		cos(-1.047197551) * 1000, sin(-1.047197551) * 1000));
	switchcordwall(&p[2], &p[3], &offset[2], setfvector2d(
		cos(-1.047197551) * 1000, sin(-1.047197551) * 1000));
}

void	rightclip(t_fvector p[4], float offset[4])
{
	switchcordwall(&p[1], &p[0], &offset[1], setfvector2d(
		cos(1.048) * 1000, sin(1.048) * 1000));
	switchcordwall(&p[3], &p[2], &offset[3], setfvector2d(
		cos(1.048) * 1000, sin(1.048) * 1000));
}

int		clip(t_fvector p[4], float offset[4])
{
	t_line l;

	if (p[0].z <= 0 && p[1].z <= 0 && p[2].z <= 0 && p[3].z <= 0)
		return (0);
	l = setline(setfvector2d(0, 0), setfvector2d(cos(-1.047197551 / 2.0)
	* 1000, sin(-1.047197551 / 2.0) * 1000), setfvector2d(p[0].z, p[0].x),
	setfvector2d(p[1].z, p[1].x));
	if (collideline(l))
		leftclip(p, offset);
	l = setline(setfvector2d(0, 0), setfvector2d(cos(1.048) * 1000,
	sin(1.048) * 1000), setfvector2d(p[0].x, p[0].z),
	setfvector2d(p[1].x, p[1].z));
	if (collideline(l))
		rightclip(p, offset);
	if (p[0].z <= 0 || p[1].z <= 0 || p[2].z <= 0 || p[3].z <= 0)
		return (0);
	return (1);
}
