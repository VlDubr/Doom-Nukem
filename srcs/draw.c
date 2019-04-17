/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:41:37 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/17 20:07:45 by gdaniel          ###   ########.fr       */
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

	cam.near = 0.1f;
	cam.far = 1000;
	cam.fov = 60;
	cam.aspectratio = (float)sizewin.y / (float)sizewin.x;
	return (cam);
}


t_mat4x4	matprojection(t_camera cam)
{
	float		fovrad;
	t_mat4x4	m;

	fovrad = 1 / tan(degrtorad(cam.fov * 0.5f));
	m = initmat(0);
	m.mat[0][0] = cam.aspectratio * fovrad;
	m.mat[1][1] = fovrad;
	m.mat[2][2] = cam.far / (cam.far - cam.near);
	m.mat[3][2] = (-cam.far * cam.near) / (cam.far - cam.near);
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

int		clip(t_player *player, t_fvector p[4])
{
	if (p[0].z <= 0 && p[1].z <= 0)
		return (0);
	if (p[0].z < 0 || p[1].z < 0 || p[2].z < 0 || p[3].z < 0)
	{
		if (p[0].z < 0)
			p[0] = inspectplane(setfvector(0, 0, 0.1f, 1), setfvector(0, 0, 1, 1), p[0], p[1]);
		if (p[1].z < 0)
			p[1] = inspectplane(setfvector(0, 0, 0.1f, 1), setfvector(0, 0, 1, 1), p[1], p[0]);
		if (p[2].z < 0)
			p[2] = inspectplane(setfvector(0, 0, 0.1f, 1), setfvector(0, 0, 1, 1), p[2], p[3]);
		if (p[3].z < 0)
			p[3] = inspectplane(setfvector(0, 0, 0.1f, 1), setfvector(0, 0, 1, 1), p[3], p[2]);
	}
	return (1);
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

void	drawsectorv2(uint32_t *p, t_player play, t_fvector *w, size_t count, size_t floor, size_t ceil)
{
	t_wall		wa;
	float		vec;
	t_fvector2d	tmp;
	t_fvector2d	delta;
	t_rgb		color;
	t_mat4x4	cammat;
	t_mat4x4	projec;
	size_t		c;

	c = 0;
	cammat = matcam(&play);
	projec = matprojection(initcam(setivector2d(800, 400)));
	while (c < count)
	{
		wa.p[0] = setfvector(w[c].x, floor, w[c].y, 1);
		wa.p[1] = setfvector(w[c + 1 >= count ? 0 : c + 1].x, floor, w[c + 1 >= count ? 0 : c + 1].y, 1);
		wa.p[2] = addfvector(wa.p[0], 0, ceil, 0);
		wa.p[3] = addfvector(wa.p[1], 0, ceil, 0);
		multmatrixdrawwall(wa.p, cammat);
		if (clip(&play, wa.p))
		{
			multmatrixdrawwall(wa.p, projec);
			wa.p[0] = divfvector(wa.p[0], wa.p[0].w, wa.p[0].w, wa.p[0].w);
			wa.p[1] = divfvector(wa.p[1], wa.p[1].w, wa.p[1].w, wa.p[1].w);
			wa.p[2] = divfvector(wa.p[2], wa.p[2].w, wa.p[2].w, wa.p[2].w);
			wa.p[3] = divfvector(wa.p[3], wa.p[3].w, wa.p[3].w, wa.p[3].w);
			adddrawwall(wa.p, 1, 1, 0);
			multdrawwall(wa.p, 400, 300, 1);
			if (!((wa.p[0].x < 0 && wa.p[1].x < 0) || (wa.p[0].x > 800 && wa.p[1].x > 800)
			|| (wa.p[2].x < 0 && wa.p[3].x < 0) || (wa.p[2].x > 800 && wa.p[3].x > 800)))
			{
				if (w[c].z == -1)
					color = setrgb(255, 255, 255);
				else
					color = setrgb(255, 0, 0);
				drawline(p, wa.p[0], wa.p[1], color);
				drawline(p, wa.p[0], wa.p[2], color);
				drawline(p, wa.p[2], wa.p[3], color);
				drawline(p, wa.p[1], wa.p[3], color);
			}
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
	SDL_RenderClear(doom->win->renderer);
	cleartexture(doom->win);

	for(int i = 0; i < doom->thismap.sectorcount; i++)
	{
		drawsectorv2(doom->win->pixels, doom->player, doom->thismap.walls +
	doom->thismap.sectors[i].start,
	doom->thismap.sectors[i].count, doom->thismap.sectors[i].floor, doom->thismap.sectors[i].height);
	}

	drawsector(doom->win->pixels, doom->player, doom->thismap.walls +
	doom->thismap.sectors[doom->player.sector].start,
	doom->thismap.sectors[doom->player.sector].count);
	drawplayer(doom->win->pixels, doom->player);

	SDL_UpdateTexture(doom->win->texture, NULL, doom->win->pixels,
	doom->win->size.x * sizeof(uint32_t));
	SDL_RenderCopy(doom->win->renderer, doom->win->texture, NULL, NULL);
	SDL_SetRenderDrawColor(doom->win->renderer, 0, 0, 0, 255);
	SDL_RenderPresent(doom->win->renderer);
}
