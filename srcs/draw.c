/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmcclure <vmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:41:37 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/26 19:20:08 by vmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

typedef struct	s_camera
{
	float		near;
	float		far;
	float		fov;
	float		aspectratio;
}				t_camera;

t_camera	initcam(t_ivector2d sizewin)
{
	t_camera cam;

	cam.near = 0.1;
	cam.far = 1000;
	cam.fov = 60;
	cam.aspectratio = (float)sizewin.x / (float)sizewin.y;
	return (cam);
}


t_mat4x4	matprojection(t_camera cam)
{
	float		fovrad;
	t_mat4x4	m;

	fovrad = 1.0 / tan(degrtorad(cam.fov/2));
	m = initmat(0);
	m.mat[0][0] = fovrad/cam.aspectratio;
	m.mat[1][1] = fovrad;
	m.mat[2][2] = (cam.near + cam.far) / (cam.far - cam.near);
	m.mat[3][2] = (-2.0*(cam.far * cam.near) )/ (cam.far - cam.near);
	m.mat[2][3] = 1;
	m.mat[3][3] = 0;
	return (m);
}

t_mat4x4	matcam(t_player *player)
{
	t_fvector	up;
	t_fvector	target;
	t_fvector	lookdir;
	t_mat4x4	cammat;

	up = setfvector(0, -1, 0, 1);
	target = setfvector(0, 0, 1, 1);
	lookdir = multipmatrix(target, matroty(player->rotate.z - 1.57f));
	target = addfvtofv(player->pos, lookdir);
	cammat = multipmattomat(mattranslate(-player->pos.x,
	-player->pos.y, -player->pos.z), matpointat(player->pos, target, up));
	cammat = multipmattomat(cammat, matrotx(player->rotate.x));
	cammat = matinverse(cammat);
	return (cammat);
}

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
	if (p1->z > p2->z)
			return (0);
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
	if (p[0].z <= 0 && p[1].z <= 0 && p[2].z <= 0 && p[3].z <= 0)
		return (0);
	offset[0] = 1;
	offset[1] = 1;
	offset[2] = 1;
	offset[3] = 1;
	tmpp[0] = p[0];
	tmpp[1] = p[1];
	tmpp[2] = p[2];
	tmpp[3] = p[3];
	// pos2 = 17;
	switchcordwall(&tmpp[0], &tmpp[1], &offset[0], setfvector2d(
			cos(-1.047197551) * 100, sin(-1.047197551) * 100));
		// printf("2Check switch %zu, %f, %f\n", c, p[1].z, tmpp[1].z);
	
	pos1 = tmpp[0].z;
	tmpp[0] = p[0];
	tmpp[1] = p[1];
	switchcordwall(&tmpp[1], &tmpp[0], &offset[1], setfvector2d(
			cos(1.047197551) * 100, sin(1.047197551) * 100));

	pos2 = tmpp[1].z;
	tmpp[0] = p[0];
	tmpp[1] = p[1];
	if (((p[0].z < pos1 || p[2].z < pos1) && offset[0] < 1))// || ((p[1].z < pos2 || p[3].z < pos2) && offset[1] < 1))
	{
		if (p[0].z <= pos1 && offset[0] < 1)
			if (!switchcordwall(&p[0], &p[1], &offset[0], setfvector2d(
				cos(-1.047197551) * 100, sin(-1.047197551) * 100)))	
				{printf("tyt1 \n");			
					return (0);		}	
		
		if (p[2].z <= pos1 && offset[0] < 1)
			if (!switchcordwall(&p[2], &p[3], &offset[2], setfvector2d(
				cos(-1.047197551) * 100, sin(-1.047197551) * 100)))
				{printf("tyt2\n");
					return (0);}
		// if (p[1].z < pos2 && offset[1] < 1)
		// 	if (!switchcordwall(&p[1], &p[0], &offset[1], setfvector2d(
		// 		cos(1.047197551) * 100, sin(1.047197551) * 100)))
		// 		{printf("tyt3\n");
		// 			return (0);
		// 		}
		// if (p[3].z < pos2 && offset[1] < 1)
		// 	if (!switchcordwall(&p[3], &p[2], &offset[3], setfvector2d(
		// 		cos(1.047197551) * 100, sin(1.047197551) * 100)))
		// 		{printf("tyt4\n");
		// 			return (0);
		// 		}
		return(1);
		
	}
	p[0] = tmpp[0];
	p[1] = tmpp[1];
	 if ( (p[1].z < pos2 || p[3].z < pos2) && offset[1] < 1)
	 {
		  
		 if (p[1].z < pos2)
				if (!switchcordwall(&p[1], &p[0], &offset[1], setfvector2d(
				cos(1.047197551) * 100, sin(1.047197551) * 100)))
				{printf("tyt3\n");
					return (0);
				}
		if (p[3].z < pos2)
				if (!switchcordwall(&p[3], &p[2], &offset[3], setfvector2d(
				cos(1.047197551) * 100, sin(1.047197551) * 100)))
				{printf("tyt4\n");
					return (0);
				}
			
		return (1);
	 }
	if (tmpp[1].z > 10 && tmpp[0].z > 10)
		return (1);
	return (0);
}

void	initdrawwall(t_fvector *view)
{
	int			y;

	y = 0;
	while (y < 4)
	{
		view[y].x = 0;
		view[y].y = 0;
		view[y].z = 0;
		view[y].w = 1;
		y++;
	}
}

void	multmatrixdrawwall(t_fvector *view, t_mat4x4 mat)
{
	view[0] = multipmatrix(view[0], mat);
	view[1] = multipmatrix(view[1], mat);
	view[2] = multipmatrix(view[2], mat);
	view[3] = multipmatrix(view[3], mat);
}

void	adddrawwall(t_fvector *view, float x, float y, float z)
{
	view[0] = addfvector(view[0], x, y, z);
	view[1] = addfvector(view[1], x, y, z);
	view[2] = addfvector(view[2], x, y, z);
	view[3] = addfvector(view[3], x, y, z);
}

void	multdrawwall(t_fvector *view, float x, float y, float z)
{
	view[0] = multfvector(view[0], x, y, z);
	view[1] = multfvector(view[1], x, y, z);
	view[2] = multfvector(view[2], x, y, z);
	view[3] = multfvector(view[3], x, y, z);
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

void	drawsector(uint32_t *p, t_player play, t_fvector *w, size_t count)
{
	t_fvector	p1;
	t_fvector	p2;
	t_rgb		color;
	size_t		c;

	c = 0;
	while (c < count)
	{
		p1 = setfvector(w[c].x, w[c].y, 0, 1);
		p2 = setfvector(w[c + 1 >= count ? 0 : c + 1].x,
		w[c + 1 >= count ? 0 : c + 1].y, 0, 1);
		p1 = subfvector(p1, play.pos.x, play.pos.z, 0);
		p2 = subfvector(p2, play.pos.x, play.pos.z, 0);
		p1 = addfvector(p1, 400, 300, 0);
		p2 = addfvector(p2, 400, 300, 0);
		if (w[c].z == -1)
			color = setrgb(255, 255, 255);
		else
			color = setrgb(255, 0, 0);
		drawline(p, p1, p2, color);
		c++;
	}
}

void	drawsectorv2(uint32_t *p, t_player play, t_fvector *w, size_t count, size_t floor, size_t ceil, t_rgb colorfloor, t_rgb colorceil, size_t i)
{
	t_wall		wa;
	float		vec;
	t_fvector	delta;
	t_fvector	tmpp[4];
	float		offset[4];
	t_rgb		color;
	t_mat4x4	cammat;
	t_mat4x4	projec;
	size_t		c;
	t_fvector2d	r;
	int x;

	x = 0;
	c = 0;
	cammat = matcam(&play);
	projec = matprojection(initcam(setivector2d(800, 800)));
	printf ("\n");
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

		if (clip(&play, wa.p, offset, c))
		{
			multmatrixdrawwall(wa.p, projec);
			tmpp[0] = wa.p[0];
			tmpp[1] = wa.p[1];
			tmpp[2] = wa.p[2];
			tmpp[3] = wa.p[3];
			if (wa.p[0].w < 1 || wa.p[1].w < 1 || wa.p[2].w < 1 || wa.p[3].w < 1)
			{
				c++;
				printf("Check\n");
				continue ;
			}
			wa.p[0] = divfvector(wa.p[0], wa.p[0].w, wa.p[0].w, wa.p[0].w);
			wa.p[1] = divfvector(wa.p[1], wa.p[1].w, wa.p[1].w, wa.p[1].w);
			wa.p[2] = divfvector(wa.p[2], wa.p[2].w, wa.p[2].w, wa.p[2].w);
			wa.p[3] = divfvector(wa.p[3], wa.p[3].w, wa.p[3].w, wa.p[3].w);


			adddrawwall(wa.p, 1, 1, 0);
			multdrawwall(wa.p, 400, 400, 1);
			if (w[c].z == -1)
				color = setrgb(255, 255, 255);
			else
				color = setrgb(255, 0, 0);
			if (wa.p[0].x > wa.p[1].x)
			{
				ft_swap((void**)&wa.p[0], (void**)&wa.p[1]);
				ft_swap((void**)&wa.p[2], (void**)&wa.p[3]);
			}
			drow_wall(p, wa, *tga, offset );
			// drawline(p, wa.p[0], wa.p[1], color);
			// drawline(p, wa.p[0], wa.p[2], color);
			// drawline(p, wa.p[2], wa.p[3], color);
			// drawline(p, wa.p[1], wa.p[3], color);
		}

		c++;
	}
}

void	drawplayer(uint32_t *p, t_player play)
{
	t_fvector	dir;

	dir.x = cos(play.rotate.z) * 5;
	dir.y = sin(play.rotate.z) * 5;
	drawline(p, setfvector(400, 300, 0, 1),
	setfvector(400 + dir.x, 300 + dir.y, 0, 1), setrgb(255, 255, 0));
}

void	draw(t_doom *doom)
{
	t_rgb	colorfloor;
	t_rgb	colorceil;
	int		i;

	SDL_RenderClear(doom->win->renderer);
	cleartexture(doom->win);
	// i = doom->thismap.sectorcount - 1;
	// while (i > -1)
	// {
	// 	switch (i)
	// 	{
	// 		case 0:
	// 			colorfloor = setrgb(0, 0, 255);
	// 			colorceil = setrgb(150, 150, 150);
	// 			break;
	// 		case 1:
	// 			colorfloor = setrgb(0, 255, 0);
	// 			colorceil = setrgb(0, 150, 150);
	// 			break;
	// 		case 2:
	// 			colorfloor = setrgb(255, 0, 0);
	// 			colorceil = setrgb(0, 0, 150);
	// 			break;
	// 		default:
	// 			colorfloor = setrgb(255, 255, 255);
	// 			colorceil = setrgb(50, 50, 50);
	// 			break;
	// 	}
	// 	drawsectorv2(doom->win->pixels, doom->player, doom->thismap.walls +
	// 	doom->thismap.sectors[i].start,
	// 	doom->thismap.sectors[i].count,
	// 	doom->thismap.sectors[i].floor,
	// 	doom->thismap.sectors[i].height, colorfloor, colorceil, i);
	// 	i--;
	// }
	colorfloor = setrgb(0, 0, 255);
	colorceil = setrgb(150, 150, 150);
	drawsectorv2(doom->win->pixels, doom->player, doom->thismap.walls +
	doom->thismap.sectors[doom->player.sector].start,
	doom->thismap.sectors[doom->player.sector].count,
	doom->thismap.sectors[doom->player.sector].floor,
	doom->thismap.sectors[i].height, colorfloor, colorceil, doom->player.sector);

	drawsector(doom->win->pixels, doom->player, doom->thismap.walls +
	doom->thismap.sectors[doom->player.sector].start,
	doom->thismap.sectors[doom->player.sector].count);
	drawplayer(doom->win->pixels, doom->player);

	drawui(doom);

	SDL_UpdateTexture(doom->win->texture, NULL, doom->win->pixels,
	doom->win->size.x * sizeof(uint32_t));
	SDL_RenderCopy(doom->win->renderer, doom->win->texture, NULL, NULL);
	SDL_SetRenderDrawColor(doom->win->renderer, 0, 0, 0, 255);
	SDL_RenderPresent(doom->win->renderer);
}
