/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:15:34 by gdaniel           #+#    #+#             */
/*   Updated: 2019/05/28 15:16:56 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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

	fovrad = 1.0 / tan(degrtorad(cam.fov / 2.0));
	m = initmat(0);
	m.mat[0][0] = fovrad / cam.aspectratio;
	m.mat[1][1] = fovrad;
	m.mat[2][2] = (cam.near + cam.far) / (cam.far - cam.near);
	m.mat[3][2] = (-2.0 * (cam.far * cam.near)) / (cam.far - cam.near);
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
