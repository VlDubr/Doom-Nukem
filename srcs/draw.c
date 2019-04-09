/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:41:37 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/09 18:42:50 by gdaniel          ###   ########.fr       */
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

t_wall	initdrawwall(t_wall w)
{
	int			y;

	y = 0;
	while (y < 4)
	{
		w.view[y].x = 0;
		w.view[y].y = 0;
		w.view[y].z = 0;
		w.view[y].w = 1;
		y++;
	}
	return (w);
}

t_wall	multmatrixdrawwall(t_wall w, t_mat4x4 mat)
{
	w.view[0] = multipmatrix(w.view[0], mat);
	w.view[1] = multipmatrix(w.view[1], mat);
	w.view[2] = multipmatrix(w.view[2], mat);
	w.view[3] = multipmatrix(w.view[3], mat);
	return (w);
}

t_wall	adddrawwall(t_wall w, float x, float y, float z)
{
	w.view[0] = addfvector(w.view[0], x, y, z);
	w.view[1] = addfvector(w.view[1], x, y, z);
	w.view[2] = addfvector(w.view[2], x, y, z);
	w.view[3] = addfvector(w.view[3], x, y, z);
	return (w);
}

t_wall	multdrawwall(t_wall w, float x, float y, float z)
{
	w.view[0] = multfvector(w.view[0], x, y, z);
	w.view[1] = multfvector(w.view[1], x, y, z);
	w.view[2] = multfvector(w.view[2], x, y, z);
	w.view[3] = multfvector(w.view[3], x, y, z);
	return (w);
}

void	calcsectorwall(t_doom *doom, t_map map, size_t secid)
{
	t_wall		wall;
	int			y;

	t_mat4x4	cammat;
	t_mat4x4	projec;

	y = 0;
	cammat = matcam(&doom->player);
	projec = matprojection(initcam(doom->win->size));
	while (y < map.sectors[secid].wallcount)
	{
		wall = map.sectors[secid].walls[y];
		wall = initdrawwall(wall);
		wall.view[0] = setfvector(map.walls[wall.sp].x, map.sectors[secid].floor, map.walls[wall.sp].y);
		wall.view[1] = setfvector(map.walls[wall.ep].x, map.sectors[secid].floor, map.walls[wall.ep].y);
		wall.view[2] = addfvector(wall.view[0], 0, map.sectors[secid].floor + map.sectors[secid].height, 0);
		wall.view[3] = addfvector(wall.view[1], 0, map.sectors[secid].floor + map.sectors[secid].height, 0);
		wall = multmatrixdrawwall(wall, cammat);
		if (clip(&doom->player, wall.view))
		{
			wall = multmatrixdrawwall(wall, projec);
			wall.view[0] = divfvector(wall.view[0], wall.view[0].w, wall.view[0].w, wall.view[0].w);
			wall.view[1] = divfvector(wall.view[1], wall.view[1].w, wall.view[1].w, wall.view[1].w);
			wall.view[2] = divfvector(wall.view[2], wall.view[2].w, wall.view[2].w, wall.view[2].w);
			wall.view[3] = divfvector(wall.view[3], wall.view[3].w, wall.view[3].w, wall.view[3].w);
			wall = adddrawwall(wall, 1, 1, 0);
			wall = multdrawwall(wall, doom->win->size.x / 2, doom->win->size.y / 2, 1);
			if (!((wall.view[0].x < 0 && wall.view[1].x < 0) || (wall.view[0].x > 800 && wall.view[1].x > 800)))
			{
				if (doom->zbuffer == NULL)
					doom->zbuffer = ft_lstnew((void*)&wall, sizeof(t_wall));
				else
					ft_lstadd(&doom->zbuffer, ft_lstnew((void*)&wall,
					sizeof(t_wall)));
			}
		}
		y++;
	}
}

void		sort(t_list	*list, size_t size)
{
	void		*v;
	t_list		*tmp;
	t_wall	t1;
	t_wall	t2;
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
			t1 = (*(t_wall*)tmp->content);
			t2 = (*(t_wall*)tmp->next->content);
			z.x = (t1.view[0].z + t1.view[1].z + t1.view[2].z + t1.view[3].z) / 4;
			z.y = (t2.view[0].z + t2.view[1].z + t2.view[2].z + t2.view[3].z) / 4;
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

void	cleartexture(t_window *win)
{
	t_ivector2d cord;

	cord.y = 0;
	while (cord.y < 600)
	{
		cord.x = 0;
		while (cord.x < 800)
		{
			win->pixels[cord.x + (cord.y * 800)] = 0;
			cord.x++;
		}
		cord.y++;
	}
}

void	draw(t_doom *doom)
{
	t_wall		w;
	size_t		count;
	t_list		*list;

	SDL_RenderClear(doom->win->renderer);
	cleartexture(doom->win);

	list = doom->zbuffer;
	if (list != NULL)
		sort(list, ft_lstsize(&list));
	while (list != NULL)
	{
		w = (*(t_wall*)list->content);
		drawwallv2(doom->win, w);
		list = list->next;
	}
	ft_lstdel(&doom->zbuffer, del);

	SDL_UpdateTexture(doom->win->texture, NULL, doom->win->pixels,
	800 * sizeof(uint32_t));
	SDL_RenderCopy(doom->win->renderer, doom->win->texture, NULL, NULL);
	SDL_SetRenderDrawColor(doom->win->renderer, 0, 0, 0, 255);
	SDL_RenderPresent(doom->win->renderer);
}
