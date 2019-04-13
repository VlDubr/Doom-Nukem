/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawwall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 18:29:39 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/09 17:58:46 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void			drawflattoptriangle(uint32_t *px, t_fvector v0,
t_fvector v1, t_fvector v2, t_rgb color)
{
	t_fvector2d	m;
	t_fvector2d	p;
	t_ivector2d	cord;
	t_ivector2d	ystartend;
	t_ivector2d	xstartend;

	m.x = (v2.x - v0.x) / (v2.y - v0.y);
	m.y = (v2.x - v1.x) / (v2.y - v1.y);
	ystartend.x = (int)ceil(v0.y - 0.5f);
	ystartend.y = (int)ceil(v2.y - 0.5f);
	cord.y = ystartend.x - 1;
	cord.y < 0 ? cord.y = -1 : 0;
	ystartend.y > 600 ? ystartend.y = 600 : 0;
	while (++cord.y < ystartend.y)
	{
		p.x = m.x * ((float)(cord.y) + 0.5f - v0.y) + v0.x;
		p.y = m.y * ((float)(cord.y) + 0.5f - v1.y) + v1.x;
		xstartend.x = (int)ceil(p.x - 0.5f);
		xstartend.y = (int)ceil(p.y - 0.5f);
		cord.x = xstartend.x - 1;
		cord.x < 0 ? cord.x = -1 : 0;
		xstartend.y > 800 ? xstartend.y = 800 : 0;
		while (++cord.x < xstartend.y)
			px[cord.x + (cord.y * 800)] = ((((((255 << 8) |
			color.red) << 8) | color.green) << 8) | color.blue);
	}
}

static void			drawflatbottomtriangle(uint32_t *px, t_fvector v0,
t_fvector v1, t_fvector v2, t_rgb color)
{
	t_fvector2d	m;
	t_fvector2d	p;
	t_ivector2d	cord;
	t_ivector2d	ystartend;
	t_ivector2d	xstartend;

	m.x = (v1.x - v0.x) / (v1.y - v0.y);
	m.y = (v2.x - v0.x) / (v2.y - v0.y);
	ystartend.x = (int)ceil(v0.y - 0.5f);
	ystartend.y = (int)ceil(v2.y - 0.5f);
	cord.y = ystartend.x - 1;
	cord.y < 0 ? cord.y = -1 : 0;
	ystartend.y > 600 ? ystartend.y = 600 : 0;
	while (++cord.y < ystartend.y)
	{
		p.x = m.x * ((float)(cord.y) + 0.5f - v0.y) + v0.x;
		p.y = m.y * ((float)(cord.y) + 0.5f - v0.y) + v0.x;
		xstartend.x = (int)ceil(p.x - 0.5f);
		xstartend.y = (int)ceil(p.y - 0.5f);
		cord.x = xstartend.x - 1;
		cord.x < 0 ? cord.x = -1 : 0;
		xstartend.y > 800 ? xstartend.y = 800 : 0;
		while (++cord.x < xstartend.y)
			px[cord.x + (cord.y * 800)] = ((((((255 << 8) |
			color.red) << 8) | color.green) << 8) | color.blue);
	}
}

void				drawfilltriswap(t_fvector *v0,
t_fvector *v1, t_fvector *v2)
{
	if (v1->y < v0->y)
		ft_swap((void**)&v0, (void**)&v1);
	if (v2->y < v0->y)
		ft_swap((void**)&v0, (void**)&v2);
	if (v1->y > v2->y)
		ft_swap((void**)&v2, (void**)&v1);
}

void				drawfilltriangle(uint32_t *p, t_fvector *v0,
t_fvector *v1, t_fvector *v2, t_rgb color)
{
	float		alpha;
	t_fvector	vi;

	if (v1->y < v0->y)
		ft_swap((void**)&v0, (void**)&v1);
	if (v2->y < v0->y)
		ft_swap((void**)&v0, (void**)&v2);
	if (v1->y > v2->y)
		ft_swap((void**)&v2, (void**)&v1);
	if (v0->y == v1->y)
	{
		if (v1->x < v0->x)
			ft_swap((void**)&v1, (void**)&v0);
		drawflattoptriangle(p, *v0, *v1, *v2, color);
	}
	else if (v1->y == v2->y)
	{
		if (v2->x < v1->x)
			ft_swap((void**)&v1, (void**)&v2);
		drawflatbottomtriangle(p, *v0, *v1, *v2, color);
	}
	else
	{
		alpha = (v1->y - v0->y) / (v2->y - v0->y);
		vi = setfvector(v0->x + (v2->x - v0->x) * alpha,
		v0->y + (v2->y - v0->y) * alpha, 0, 1);
		if (v1->x < vi.x)
		{
			drawflattoptriangle(p, *v1, vi, *v2, color);
			drawflatbottomtriangle(p, *v0, *v1, vi, color);
		}
		else
		{
			drawflattoptriangle(p, vi, *v1, *v2, color);
			drawflatbottomtriangle(p, *v0, vi, *v1, color);
		}
	}
}

void	drawceil(uint32_t *p, t_fvector *v2, t_fvector *v3, t_rgb color)
{
	t_fvector2d	cord;
	t_fvector2d	end;

	cord.x = v2->x < v3->x ? v2->x : v3->x;
	end.x = v2->x < v3->x ? v3->x : v2->x;
	while (cord.x < end.x)
	{
		cord.y = 0;
		end.y = v2->y < v3->y ? v3->y : v2->y;
		while (cord.y < end.y)
		{
			if (cord.x >= 0 && cord.x < 800 && cord.y >= 0 && cord.y < 600)
				p[(int)(cord.x + (cord.y * 800))] = ((((((255 << 8) |
				color.red) << 8) | color.green) << 8) | color.blue);
			cord.y++;
		}
		cord.x++;
	}
}

void	drawfloor(uint32_t *p, t_fvector *v0, t_fvector *v1, t_rgb color)
{
	t_fvector2d	cord;
	t_fvector2d	end;

	cord.x = v0->x < v1->x ? v0->x : v1->x;
	end.x = v0->x < v1->x ? v1->x : v0->x;
	while (cord.x < end.x)
	{
		cord.y = v0->y < v1->y ? v0->y : v1->y;
		end.y = 800;
		while (cord.y < end.y)
		{
			if (cord.x >= 0 && cord.x < 800 && cord.y >= 0 && cord.y < 600)
				p[(int)(cord.x + (cord.y * 800))] = ((((((255 << 8) |
				color.red) << 8) | color.green) << 8) | color.blue);
			cord.y++;
		}
		cord.x++;
	}
}

// void	drawwallv2(t_window *win, t_wall w)
// {
// 	t_rgb color;

// 	drawceil(win->pixels, &w.view[2], &w.view[3], setrgb(150, 150, 150));
// 	if (w.nextsector == -1)
// 		color = setrgb(255, 255, 255);
// 	else
// 		color = setrgb(255, 0, 0);
// 	drawfilltriangle(win->pixels, &w.view[0], &w.view[1], &w.view[3], color);
// 	drawfilltriangle(win->pixels, &w.view[0], &w.view[2], &w.view[3], color);
// }
