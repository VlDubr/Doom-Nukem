/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:41:37 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/08 17:11:25 by gdaniel          ###   ########.fr       */
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
	t_fvector dist;

	if (p[0].z <= 0 && p[1].z <= 0)
		return (0);
	if (p[0].z < 0 || p[1].z < 0)
	{
		dist.x = 0.1f + p[0].z - 0.1f;
		dist.y = 0.1f + p[1].z - 0.1f;
		if (dist.x < 0)
		{
			p[0] = inspectplane(setfvector(0, 0, 0.1f), setfvector(0, 0, 1), p[0], p[1]);
			p[2] = inspectplane(setfvector(0, 0, 0.1f), setfvector(0, 0, 1), p[2], p[3]);
		}
		if (dist.y < 0)
		{
			p[1] = inspectplane(setfvector(0, 0, 0.1f), setfvector(0, 0, 1), p[1], p[0]);
			p[3] = inspectplane(setfvector(0, 0, 0.1f), setfvector(0, 0, 1), p[3], p[2]);
		}
	}
	return (1);
}

t_drawwall	multmatrixdrawwall(t_drawwall w, t_mat4x4 mat)
{
	w.p[0] = multipmatrix(w.p[0], mat);
	w.p[1] = multipmatrix(w.p[1], mat);
	w.p[2] = multipmatrix(w.p[2], mat);
	w.p[3] = multipmatrix(w.p[3], mat);
	return (w);
}

t_drawwall	adddrawwall(t_drawwall w, float x, float y, float z)
{
	w.p[0] = addfvector(w.p[0], x, y, z);
	w.p[1] = addfvector(w.p[1], x, y, z);
	w.p[2] = addfvector(w.p[2], x, y, z);
	w.p[3] = addfvector(w.p[3], x, y, z);
	return (w);
}

t_drawwall	multdrawwall(t_drawwall w, float x, float y, float z)
{
	w.p[0] = multfvector(w.p[0], x, y, z);
	w.p[1] = multfvector(w.p[1], x, y, z);
	w.p[2] = multfvector(w.p[2], x, y, z);
	w.p[3] = multfvector(w.p[3], x, y, z);
	return (w);
}

void	calcsectorwall(t_doom *doom, t_map map, size_t secid)
{
	t_wall		wall;
	int			y;

	t_mat4x4	cammat;
	t_mat4x4	projec;

	t_drawwall	w;

	y = 0;
	cammat = matcam(&doom->player);
	projec = matprojection(initcam(doom->win->size));
	while (y < map.sectors[secid].wallcount)
	{
		wall = map.sectors[secid].walls[y];
		w.p[0] = setfvector(map.walls[wall.sp].x, map.sectors[secid].floor, map.walls[wall.sp].y);
		w.p[1] = setfvector(map.walls[wall.ep].x, map.sectors[secid].floor, map.walls[wall.ep].y);
		w.p[2] = addfvector(w.p[0], 0, map.sectors[secid].floor + map.sectors[secid].height, 0);
		w.p[3] = addfvector(w.p[1], 0, map.sectors[secid].floor + map.sectors[secid].height, 0);
		w = multmatrixdrawwall(w, cammat);
		if (clip(&doom->player, w.p))
		{
			w = multmatrixdrawwall(w, projec);
			w.p[0] = divfvector(w.p[0], w.p[0].w, w.p[0].w, w.p[0].w);
			w.p[1] = divfvector(w.p[1], w.p[1].w, w.p[1].w, w.p[1].w);
			w.p[2] = divfvector(w.p[2], w.p[2].w, w.p[2].w, w.p[2].w);
			w.p[3] = divfvector(w.p[3], w.p[3].w, w.p[3].w, w.p[3].w);
			w = adddrawwall(w, 1, 1, 0);
			w = multdrawwall(w, doom->win->size.x / 2, doom->win->size.y / 2, 0);
			SDL_SetRenderDrawColor(doom->win->renderer, 255, 255, 255, 255);
			drawwall(doom->win->renderer, w);
			SDL_SetRenderDrawColor(doom->win->renderer, 255, 0, 0, 255);
			SDL_RenderDrawLine(doom->win->renderer, w.p[0].x, w.p[0].y, w.p[1].x, w.p[1].y);
			SDL_RenderDrawLine(doom->win->renderer, w.p[0].x, w.p[0].y, w.p[2].x, w.p[2].y);
			SDL_RenderDrawLine(doom->win->renderer, w.p[2].x, w.p[2].y, w.p[3].x, w.p[3].y);
			SDL_RenderDrawLine(doom->win->renderer, w.p[1].x, w.p[1].y, w.p[3].x, w.p[3].y);
			// if (doom->zbuffer == NULL)
			// 	doom->zbuffer = ft_lstnew((void*)&w, sizeof(t_drawwall));
			// else
			// 	ft_lstadd(&doom->zbuffer, ft_lstnew((void*)&w,
			// 	sizeof(t_drawwall)));
		}
		y++;
	}
}

void		sort(t_list	*list, size_t size)
{
	void		*v;
	t_list		*tmp;
	t_drawwall	t1;
	t_drawwall	t2;
	t_fvector2d	z;
	int			i;
	int			y;

	i = 1;
	while (i == 1)
	{
		tmp = list;
		i = 0;
		y = 0;
		while (tmp != NULL && tmp->next != NULL)
		{
			t1 = (*(t_drawwall*)tmp->content);
			t2 = (*(t_drawwall*)tmp->next->content);
			z.x = (t1.p[0].z + t1.p[1].z + t1.p[2].z) / 3.0f;
			z.y = (t2.p[0].z + t2.p[1].z + t2.p[2].z) / 3.0f;
			if (z.x < z.y)
			{
				ft_swap(&tmp->content, &tmp->next->content);
				i = 1;
			}
			tmp = tmp->next;
		}
	}
}

void		del(void *data, size_t size)
{
	if (!data)
		return ;
	free(data);
}

void	draw(t_doom *doom)
{
	t_drawwall	w;
	size_t		count;
	t_list		*list;

	count = -1;
	SDL_RenderClear(doom->win->renderer);
	while (++count < doom->thismap.sectorcount)
		calcsectorwall(doom, doom->thismap, count);
	// list = doom->zbuffer;
	// SDL_SetRenderDrawColor(doom->win->renderer, 255, 255, 255, 255);
	// while (list != NULL)
	// {
	// 	w = (*(t_drawwall*)list->content);
	// 	drawwall(doom->win->renderer, w);
	// 	list = list->next;
	// }
	SDL_SetRenderDrawColor(doom->win->renderer, 0, 0, 0, 255);
	SDL_RenderPresent(doom->win->renderer);
}
