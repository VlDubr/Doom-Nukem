/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:41:37 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/04 21:20:22 by gdaniel          ###   ########.fr       */
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
	t_mat4x4	cammat;

	up = setfvector(0, -1, 0);
	target = setfvector(0, 0, 1);
	player->lookdir = multipmatrix(target, matroty(player->rotate.y));
	target = addfvtofv(player->pos, player->lookdir);

	cammat = multipmattomat(mattranslate(-player->pos.x,
	-player->pos.y, -player->pos.z), matpointat(player->pos, target, up));
	cammat = multipmattomat(cammat, matrotx(player->rotate.x));

	cammat = matinverse(cammat);
	return (cammat);
}

static float distance(t_fvector vec)
{
	//vec = normfvector(vec);
	return (0 * vec.x + 0 * vec.y + 0.1f + vec.z - 0.1f);
}

t_fvector	inspectplane(t_fvector planep, t_fvector planen,
t_fvector linestart, t_fvector lineend)
{
	t_fvector	linestarttoend;
	t_fvector	linetoinspector;
	float planed;
	float ad;
	float bd;
	float t;

	planen = normfvector(planen);
	planed = -dotproductfvtofv(planen, planep);
	ad = dotproductfvtofv(linestart, planen);
	bd = dotproductfvtofv(lineend, planen);
	t = (-planed - ad) / (bd - ad);
	linestarttoend = subfvtofv(lineend, linestart);
	linetoinspector = multfvector(linestarttoend, t, t, t);
	return (addfvtofv(linestart, linetoinspector));
}

int		clip(t_player *player, t_fvector p[4])
{
	t_fvector dist;

	if (p[0].z <= 0 && p[1].z <= 0)
		return (0);
	if (p[0].z < 0 || p[1].z < 0)
	{
		dist.x = distance(p[0]);
		dist.y = distance(p[1]);

		if (dist.x < 0)
		{
			p[0] = inspectplane(setfvector(0, 0, 0.1f), setfvector(0, 0, 1), p[0], p[1]);
			p[3] = inspectplane(setfvector(0, 0, 0.1f), setfvector(0, 0, 1), p[3], p[4]);
		}

		//if (dist.y < 0)
		//	p[1] = inspectplane(setfvector(0, 0, 0.1f), setfvector(0, 0, 1), p[1], p[0]);
		//return (0);
	}
	return (1);
}

void	drawsector(t_window *win, t_player *player, t_map map, size_t secid)
{
	t_wall		wall;
	int			y;

	t_mat4x4	cammat;
	t_mat4x4	projec;

	t_fvector	p[4];

	y = 0;
	cammat = matcam(player);
	projec = matprojection(initcam(win->size));
	while (y < map.sectors[secid].wallcount)
	{
		wall = map.sectors[secid].walls[y];

		p[0] = setfvector(map.walls[wall.sp].x, map.sectors[secid].floor, map.walls[wall.sp].y);
		p[1] = setfvector(map.walls[wall.ep].x, map.sectors[secid].floor, map.walls[wall.ep].y);
		p[2] = addfvector(p[0], 0, map.sectors[secid].floor + map.sectors[secid].height, 0);
		p[3] = addfvector(p[1], 0, map.sectors[secid].floor + map.sectors[secid].height, 0);

		p[0] = multipmatrix(p[0], cammat);
		p[1] = multipmatrix(p[1], cammat);
		p[2] = multipmatrix(p[2], cammat);
		p[3] = multipmatrix(p[3], cammat);

		if (clip(player, p))
		{
			p[0] = multipmatrix(p[0], projec);
			p[1] = multipmatrix(p[1], projec);
			p[2] = multipmatrix(p[2], projec);
			p[3] = multipmatrix(p[3], projec);

			p[0] = divfvector(p[0], p[0].w, p[0].w, p[0].w);
			p[1] = divfvector(p[1], p[1].w, p[1].w, p[1].w);
			p[2] = divfvector(p[2], p[2].w, p[2].w, p[2].w);
			p[3] = divfvector(p[3], p[3].w, p[3].w, p[3].w);

			p[0] = addfvector(p[0], 1, 1, 0);
			p[1] = addfvector(p[1], 1, 1, 0);
			p[2] = addfvector(p[2], 1, 1, 0);
			p[3] = addfvector(p[3], 1, 1, 0);

			p[0] = multfvector(p[0], win->size.x / 2, win->size.y / 2, 0);
			p[1] = multfvector(p[1], win->size.x / 2, win->size.y / 2, 0);
			p[2] = multfvector(p[2], win->size.x / 2, win->size.y / 2, 0);
			p[3] = multfvector(p[3], win->size.x / 2, win->size.y / 2, 0);

			if (wall.nextsector == -1)
				SDL_SetRenderDrawColor(win->renderer, 255, 255, 255, 255);
			else
				SDL_SetRenderDrawColor(win->renderer, 255, 0, 0, 255);
			SDL_RenderDrawLine(win->renderer, p[0].x, p[0].y, p[1].x, p[1].y);
			SDL_RenderDrawLine(win->renderer, p[0].x, p[0].y, p[2].x, p[2].y);
			SDL_RenderDrawLine(win->renderer, p[2].x, p[2].y, p[3].x, p[3].y);
			SDL_RenderDrawLine(win->renderer, p[1].x, p[1].y, p[3].x, p[3].y);
		}
		y++;
	}
}

void	draw(t_doom *doom)
{
	size_t count;

	count = 0;
	SDL_RenderClear(doom->win->renderer);
	while (count < doom->thismap.sectorcount)
	{
		drawsector(doom->win, &doom->player, doom->thismap, count);
		count++;
	}
	SDL_SetRenderDrawColor(doom->win->renderer, 0, 0, 0, 255);
	SDL_RenderPresent(doom->win->renderer);
}
