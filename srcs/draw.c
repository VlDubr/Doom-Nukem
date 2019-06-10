/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:41:37 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/10 17:03:27 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_fvector	inspectplane(t_fvector planep, t_fvector planen,
t_fvector linestart, t_fvector lineend)
{
	t_fvector	linestarttoend;
	t_fvector	linetoinspector;
	t_fvector	planedadbd;
	float t;

	planen = normfvector(planen);
	planedadbd.x = -dotproductfvtofv(planen, planep);
	planedadbd.y = dotproductfvtofv(linestart, planen);
	planedadbd.z = dotproductfvtofv(lineend, planen);
	t = (-planedadbd.x - planedadbd.y) /
	(planedadbd.z - planedadbd.y);
	linestarttoend = subfvtofv(lineend, linestart);
	linetoinspector = multfvector(linestarttoend, t, t, t);
	return (addfvtofv(linestart, linetoinspector));
}

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
	t_fvector2d ret;
	t_fvector	tmpp;
	t_line l;

	t1 = sqrt((fabs(p2->x - p1->x) * fabs(p2->x - p1->x)) +
	(fabs(p2->z - p1->z) * fabs(p2->z - p1->z)));
	l = setline(setfvector2d(p1->x, p1->z), setfvector2d(p2->x, p2->z),
	setfvector2d(0, 0), setfvector2d(angle.x * 100, angle.y * 100));
	crossline(l, &ret);
	tmpp = *p1;
	p1->x = ret.x;
	p1->z = ret.y;
	// if (p1->z > p2->z)
	// 		return (0);
	t2 = sqrt((fabs(p2->x - p1->x) * fabs(p2->x - p1->x))
	+ (fabs(p2->z - p1->z) * fabs(p2->z - p1->z)));
	*offset = t2/t1;
	p1->y = flerp(tmpp.y, p2->y, 1 - (*offset));
	p1->w = flerp(tmpp.w, p2->w, 1 - (*offset));
	return (1);
}

int		clip(t_player *player, t_fvector p[4], float offset[4], size_t c)
{
	float		t1;
	float		t2;
	t_fvector2d ret;
	t_fvector	 tmpp[4];
	t_line l;
	float pos;
	float pos1;
	float pos2;
	int peresechenie;
	peresechenie = 1;
	if (p[0].z <= 0 && p[1].z <= 0 && p[2].z <= 0 && p[3].z <= 0)
		return (0);

	l.p[0].x = 0;
	l.p[0].y = 0;
	l.p[1].x = cos(-1.047197551/2.0) * 1000;
	l.p[1].y = sin(-1.047197551/2.0) * 1000;
	l.p[2].x = p[0].z;
	l.p[2].y = p[0].x;
	l.p[3].x = p[1].z;
	l.p[3].y = p[1].x;
	peresechenie = collideline(l);

	if (peresechenie == 1)
	{

		switchcordwall(&p[0], &p[1], &offset[0], setfvector2d(
			cos(-1.047197551) * 1000, sin(-1.047197551) * 1000));
		switchcordwall(&p[2], &p[3], &offset[2], setfvector2d(
			cos(-1.047197551) * 1000, sin(-1.047197551) * 1000));
	}//-1.047197551 1.048
	l.p[0].x = 0;
	l.p[0].y = 0;
	l.p[1].x = cos(1.048) * 1000;
	l.p[1].y = sin(1.048) * 1000;
	l.p[2].x = p[0].x;
	l.p[2].y = p[0].z;
	l.p[3].x = p[1].x;
	l.p[3].y = p[1].z;
	peresechenie = collideline(l);
	// printf ("%zu - %d\n", c, peresechenie);
	 if (peresechenie == 1)
	 {
		switchcordwall(&p[1], &p[0], &offset[1], setfvector2d(
			cos(1.048) * 1000, sin(1.048) * 1000));
		switchcordwall(&p[3], &p[2], &offset[3], setfvector2d(
			cos(1.048) * 1000, sin(1.048) * 1000));
	 }
	 if (p[0].z <= 0 || p[1].z <= 0 || p[2].z <= 0 || p[3].z <= 0)
		return (0);
	return (1);
}

void	cleartexture(t_window *win)
{
	t_ivector2d cord;

	cord.y = 0;
	while (cord.y < win->size.y)
	{
		cord.x = 0;
		while (cord.x < win->size.x)
		{
			win->pixels[cord.x + (cord.y * win->size.x)] = 0;
			cord.x++;
		}
		cord.y++;
	}
}

t_fvector	*clipforfloor(t_player *player, t_fvector p[4], float offset[4], size_t c)
{
	float		t1;
	float		t2;
	t_fvector2d ret;
	t_fvector	*chek;
	t_fvector	 tmpp[4];
	t_line l;
	t_line cline;
	int i;
	i = 0;
	float pos;
	float pos1;
	float pos2;
	int peresechenie;
	float x, y;
	chek = (t_fvector*)malloc(sizeof(t_fvector) * 2);
	peresechenie = 1;
	l.p[0].x = 0;
	l.p[0].y = 0;
	l.p[1].x = 1000;
	l.p[1].y = 0;
	while (i < 4)
	{
		l.p[2].x = p[i].z;
		l.p[2].y = p[i].x;
		l.p[3].x = p[i+1 == 4 ? 0 : i+1].z;
		l.p[3].y = p[i+1 == 4 ? 0 : i+1].x;
		peresechenie = collideline(l);
		if (peresechenie == 1)
		{
			crossline(l, &ret);
			chek[0] = setfvector(ret.y, p[i].y, ret.x, p[i].w);
			// printf("%d\n", i);
			// printf("a\n");
			
			// return (setfvector(0, p[i].y, ret.x, 1));
		}
		i++;
	}
	return (chek);
}

void	drawsectorv2(t_doom *doom, t_fvector *w, size_t count, size_t floor, size_t ceil, size_t i, t_tga texture)
{
	t_wall		wa;
	t_wall		fl;
	double		offloor[4];
	float		vec;
	t_fvector	delta;
	t_fvector	tmpp[4];
	float		offset[4];
	t_rgb		color;
	t_mat4x4	cammat;
	t_mat4x4	projec;
	size_t		c;
	t_fvector2d	r;

	// t_fvector	*fl;
	int x;
	t_rgb color1;
	float dx;
	float dy;
	float maxdelt;
	int kef;
	x = 0;
	c = 0;
	cammat = matcam(&doom->player);
	projec = matprojection(initcam(setivector2d(800, 800)));

	//calculate floor
	// t_fvector2d min;
	// t_fvector2d max;

	// min = setfvector2d(w[0].x, w[0].y);
	// max = setfvector2d(w[0].x, w[0].y);
	// while (c < count)
	// {
	// 	min.x = ft_fmin(min.x, w[c].x);
	// 	min.y = ft_fmin(min.y, w[c].y);
	// 	max.x = ft_fmax(max.x, w[c].x);
	// 	max.y = ft_fmax(max.y, w[c].y);
	// 	c++;
	// }
	// if (i == 0)
	
	// fl.p[0] = setfvector(-500, floor, -500, 1);
	// fl.p[1] = setfvector(-500, floor, 500, 1);
	// fl.p[2] = setfvector(500, floor, 500, 1);
	// fl.p[3] = setfvector(500, floor, -500, 1);
	// fl.texture = texture;
	// maxdelt = fabsf (wa.p[2].x - wa.p[0].x);
	// if (fabsf(wa.p[2].z - wa.p[0].z) > fabsf(wa.p[2].x - wa.p[0].x))
	// 	maxdelt = fabsf (wa.p[2].z - wa.p[0].z);
	//multmatrixdrawwall(fl.p, cammat);
	// dx = wa.p[2].x - wa.p[0].x;
	// dy = wa.p[2].z - wa.p[0].z;
	// dx = sqrt((dx * dx) + (dy * dy));
	// offloor[0] = fabsf((wa.p[0].x) / dx);
	// offloor[1] = 1 - fabsf(( wa.p[0].z) / dy);
	// if (i == 0)
	// 	printf ("%f \n", offloor[0] );
	//c = 0;
	//fl = clipforfloor(&play, wa.p, offset, i);
	//multmatrixdrawwall(fl.p, projec);
	// fl[0] = divfvector(fl[0], fl[0].w, fl[0].w, fl[0].w);
	// fl[0] = addfvector(fl[0], 1, 1, 0);
	// fl[0] = multfvector(fl[0], 400, 400, 1);
	// offloor[0] = (play.pos.z - min.y)/(max.y - min.y);
	// offloor[1] = 1.0-(play.pos.x - min.x)/(max.x - min.x);
	// fl[1].x = 800.0 * dx / 1000 * 20;
	// fl[1].y = 800.0 * dy / 500;
	// if (i == 0)
	// 	printf ("%f %f %f dy %f\n", fl[0].y , offloor[1], offloor[0], max.x - min.x );
	//calculate wall
		
	c = 0;
	while (c < count)
	{
		wa.p[0] = setfvector(w[c].x, floor, w[c].y, 1);
		wa.p[1] = setfvector(w[c + 1 >= count ? 0 : c + 1].x, floor, w[c + 1 >= count ? 0 : c + 1].y, 1);
		wa.p[2] = addfvector(wa.p[0], 0, ceil, 0);
		wa.p[3] = addfvector(wa.p[1], 0, ceil, 0);
		multmatrixdrawwall(wa.p, cammat);
		offset[0] = 1;
		offset[1] = 1;
		offset[2] = 1;
		offset[3] = 1;

		if (clip(&doom->player, wa.p, offset, c))
		{
			wallproj(wa.p, projec);
			if (w[c].z == -1)
				color = setrgb(255, 255, 255);
			else
				color = setrgb(255, 0, 0);
			if (wa.p[0].x > wa.p[1].x)
			{
				ft_swap((void**)&wa.p[0], (void**)&wa.p[1]);
				ft_swap((void**)&wa.p[2], (void**)&wa.p[3]);
				ft_swap((void**)&offset[1], (void**)&offset[0]);
			}
			wa.offset[0] = offset[0];
			wa.offset[1] = offset[1];
			wa.offset[2] = offset[2];
			wa.offset[3] = offset[3];
			wa.texture = texture;
			// if (w[c].z == -1)			
			// 	drow_wall(doom->win->pixels, wa, texture, offset);
			if (w[c].z == -1)
				addwallinlist(&doom->pipeline, wa);
			// printf ("%f %f %f %f\n", fl.x, fl.y, fl.z, fl.w);
			//if (i == 0 )
			//	drawfloor(doom, wa, offloor, fl);
			// drawline(doom->win->pixels, wa.p[0], wa.p[1], color);
			// drawline(doom->win->pixels, wa.p[0], wa.p[2], color);
			// drawline(doom->win->pixels, wa.p[2], wa.p[3], color);
			// drawline(doom->win->pixels, wa.p[1], wa.p[3], color);
		}
		c++;
		color1 = setrgb(255, 0, 255);
	}
	// if (fl[0].x < 800 && fl[0].x > 0 && fl[0].y > 0 && fl[0].y < 800)
	// 	p[(int)fl[0].x + ((int)fl[0].y * 800)] = ((((((255 << 8) | 255) << 8) | 0) << 8) | 243);
	// free(fl);
}

void	drawwall(t_doom *doom)
{
	t_list	*tmp;
	t_wall	*wall;

	tmp = doom->pipeline;
	while (tmp != NULL)
	{
		wall = (t_wall*)tmp->content;
		if (wall->type != 2)
			drow_wall(doom->win->pixels, *wall, wall->texture, wall->offset);
		// if (wall->type == 3 || wall->type == 1 || wall->type == 2)
		// 	//drawfloor(doom, *wall, wall->type);
		// if (wall->type == 3 || wall->type == 4 || wall->type == 5)
		// 	//drawcail(doom, *wall, wall->type);
		tmp = tmp->next;
	}
}

void	proj(t_doom *doom, t_mat4x4 projec, t_wall wa)
{
	if (clip(&doom->player, wa.p, wa.offset, wa.c))
	{
		wallproj(wa.p, projec);
		if (wa.p[0].x > wa.p[1].x)
		{
			ft_swap((void**)&wa.p[0], (void**)&wa.p[1]);
			ft_swap((void**)&wa.p[2], (void**)&wa.p[3]);
			ft_swap((void**)&wa.offset[1], (void**)&wa.offset[0]);
		}
		addwallinlist(&doom->pipeline, wa);
	}
}

void	loopdrawwall(t_doom *doom, t_wall **wa, int count, t_sermat mat)
{
	int i;

	i = 0;
	while (i <= count)
	{
		multmatrixdrawwall((*wa)[i].p, mat.cammat);
		proj(doom, mat.projec, (*wa)[i]);
		i++;
	}
}

void	drawwallv3(t_doom *doom, size_t sec)
{
	t_wall		*wa;
	t_sermat	mat;
	t_sector	sect;
	t_ivector	ci;

	mat.cammat = matcam(&doom->player);
	mat.projec = matprojection(initcam(setivector2d(800, 800)));
	sect = doom->thismap.sectors[sec];
	if ((wa = (t_wall*)ft_memalloc(sizeof(t_wall) * 2)) == NULL)
		error("Error");
	ci.x = sect.start;
	ci.y = -1;
	doom->visit[sec] = 1;
	while (++ci.y < sect.count)
	{
		ci.z = setwalls(doom, &wa, sect, ci);
		loopdrawwall(doom, &wa, ci.z, mat);
	}
	ft_memdel((void**)&wa);
}

void	draw(t_doom *doom)
{
	doom->pipeline = NULL;
	drawwallv3(doom, doom->player.sector);
	SDL_RenderClear(doom->win->renderer);
	cleartexture(doom->win);
	drawskubox(doom);
	drawobj(doom, doom->thismap);
	//clock_t start = clock();
	drawsort(doom->pipeline);
	drawwall(doom);
	//clock_t end = clock();
	//double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	//printf("The time: %f seconds\n", seconds);
	ft_lstdel(&doom->pipeline, del);
	drawminimap(doom->win->pixels, doom, doom->player.sector,
	setivector2d(400, 300));
	drawweapon(doom);
	drawammo(doom);
	drawui(doom);
	SDL_UpdateTexture(doom->win->texture, NULL, doom->win->pixels,
	doom->win->size.x * sizeof(uint32_t));
	SDL_RenderCopy(doom->win->renderer, doom->win->texture, NULL, NULL);
	SDL_SetRenderDrawColor(doom->win->renderer, 0, 0, 0, 255);
	SDL_RenderPresent(doom->win->renderer);
}
